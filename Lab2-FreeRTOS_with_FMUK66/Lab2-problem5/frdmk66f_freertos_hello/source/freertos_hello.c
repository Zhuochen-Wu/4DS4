/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_uart.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

EventGroupHandle_t event_group_global_handler;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LEFT_BIT (1 << 0)
#define RIGHT_BIT (1 << 1)
#define UP_BIT (1 << 2)
#define DOWN_BIT (1 << 3)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#define TARGET_UART UART4

void setupUART() {
	uart_config_t config;
	UART_GetDefaultConfig(&config);

	config.baudRate_Bps = 57600;
	config.enableTx = true;
	config.enableRx = true;
	config.enableRxRTS = true;
	config.enableTxCTS = true;

	UART_Init(TARGET_UART, &config, CLOCK_GetFreq(kCLOCK_BusClk));

	/******** Enable Interrupts *********/
	UART_EnableInterrupts(TARGET_UART, kUART_RxDataRegFullInterruptEnable);
	NVIC_SetPriority(UART4_RX_TX_IRQn, 2);
	EnableIRQ(UART4_RX_TX_IRQn);
}

void UART4_RX_TX_IRQHandler() {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	UART_GetStatusFlags(TARGET_UART);

	char ch = UART_ReadByte(TARGET_UART);
	switch (ch) {
		case 'a':
			xEventGroupSetBitsFromISR(event_group_global_handler, LEFT_BIT, &
				xHigherPriorityTaskWoken);
		break;
		case 's':
			xEventGroupSetBitsFromISR(event_group_global_handler, DOWN_BIT, &
				xHigherPriorityTaskWoken);
		break;
		case 'd':
			xEventGroupSetBitsFromISR(event_group_global_handler, RIGHT_BIT, &
				xHigherPriorityTaskWoken);
		break;
		case 'w':
			xEventGroupSetBitsFromISR(event_group_global_handler, UP_BIT, &
				xHigherPriorityTaskWoken);
		break;
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void consumer_event(void *pvParameters) {
	EventGroupHandle_t event_group = (EventGroupHandle_t) pvParameters;
	EventBits_t bits;

	while (1) {
		bits = xEventGroupWaitBits(
					event_group,
					LEFT_BIT | RIGHT_BIT | UP_BIT | DOWN_BIT,
					pdTRUE,
					pdFALSE,
					portMAX_DELAY);

		if ((bits & LEFT_BIT) == LEFT_BIT) {
			PRINTF("Left\r\n");
		}
		if ((bits & RIGHT_BIT) == RIGHT_BIT) {
			PRINTF("Right\r\n");
		}
		if ((bits & UP_BIT) == UP_BIT) {
			PRINTF("Up\r\n");
		}
		if ((bits & DOWN_BIT) == DOWN_BIT) {
			PRINTF("Down\r\n");
		}
	}
}

void delay(void){
	for (int i=0; i< 800000; i++){
		__asm("NOP"); /* delay */
	}
}

/*!
 * @brief Application entry point.
 */
int main(void) {

	BaseType_t status;
//	char txbuff[] = "Hello World\r\n";

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	setupUART();

//	for (int i=0; i<5; i++){
//		UART_WriteBlocking(TARGET_UART, txbuff, sizeof(txbuff) - 1);
//		delay();
//		printf("Sent: %s", txbuff);
//	}

	event_group_global_handler = xEventGroupCreate();
	status = xTaskCreate(consumer_event, "consumer", 200,
			(void*) event_group_global_handler, 3, NULL);

	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}
	vTaskStartScheduler();
		while (1)
		{}
}
