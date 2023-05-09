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

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"


#define STR_LEN		16

void hello_task(void *pvParameters)
{
	QueueHandle_t queue1 = (QueueHandle_t)pvParameters;
	BaseType_t status;
	PRINTF("Type string\r\n");
	char str[STR_LEN];
	scanf("%s",str);
	status = xQueueSendToBack(queue1, (void*) str, portMAX_DELAY);
	if (status != pdPASS)
	{
		PRINTF("Queue Send failed!.\r\n");
		while (1);
	}

	vTaskDelete(NULL);
}

void hello_task2(void *pvParameters)
{
	QueueHandle_t queue1 = (QueueHandle_t)pvParameters;
	BaseType_t status;
	char string[STR_LEN];
	status = xQueueReceive(queue1, (void *) string, portMAX_DELAY);
	if (status != pdPASS)
	{
		PRINTF("Queue Receive failed!.\r\n");
		while (1);
	}
	while(1)
	{
		PRINTF("String: %s\r\n", string);
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
	QueueHandle_t queue1 = xQueueCreate(1, sizeof(char)*STR_LEN);
	if (queue1 == NULL)
	{
		PRINTF("Queue creation failed!.\r\n");
		while (1);
	}
	status = xTaskCreate(hello_task, "hello task", 200, (void*)queue1, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}
	status = xTaskCreate(hello_task2, "hello task2", 200, (void*)queue1, 3, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}
	vTaskStartScheduler();
	while (1)
	{}
}
