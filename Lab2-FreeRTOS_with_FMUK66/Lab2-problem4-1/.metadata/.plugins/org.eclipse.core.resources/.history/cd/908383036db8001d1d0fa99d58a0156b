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
#include "semphr.h"
#include "string.h"
#include "ctype.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"


char str[16];

void hello_task(void *pvParameters)
{
	PRINTF("Type string\r\n");
	scanf("%s", str);
	xSemaphoreGive(*((SemaphoreHandle_t*)pvParameters));
    vTaskDelete(NULL);

}

void hello_task2(void *pvParameters)
{
	while(1)
	{
		BaseType_t status = xSemaphoreTake(*((SemaphoreHandle_t*)pvParameters), 0);
		if (status == pdPASS) {
			xSemaphoreGive(*((SemaphoreHandle_t*)pvParameters));
			PRINTF("%s\r\n", str);
		}
//		else {
//			PRINTF("Failed to acquire consumer_semaphore\r\n");
//		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void hello_task3(void *pvParameters)
{
	char s[16];
	while(1)
	{
		BaseType_t status = xSemaphoreTake(*((SemaphoreHandle_t*)pvParameters), 0);
		if (status == pdPASS) {
			char *p = str;
			int i=0;
		    while(*p)
		    	s[i++] = toupper(*(p++));
		    s[i] = *p; // termination char
			PRINTF("%s\r\n", s);
			xSemaphoreGive(*((SemaphoreHandle_t*)pvParameters));
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

int main(void)
{
	BaseType_t status;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();


	SemaphoreHandle_t *sem = (SemaphoreHandle_t *) malloc(sizeof(SemaphoreHandle_t));
	sem[0] = xSemaphoreCreateBinary();

	status = xTaskCreate(hello_task, "Hello_task", 200, sem, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}

	status = xTaskCreate(hello_task2, "Hello_task2", 200, sem, 3, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}

	status = xTaskCreate(hello_task3, "Hello_task3", 200, sem, 3, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}

	vTaskStartScheduler();
	for (;;);
}
