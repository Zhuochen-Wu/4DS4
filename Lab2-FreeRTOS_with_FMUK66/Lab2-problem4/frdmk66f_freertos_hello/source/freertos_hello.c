

#include <stdio.h>
#include <ctype.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"


#define LEFT_BIT (1 << 0)
#define RIGHT_BIT (1 << 1)
#define UP_BIT (1 << 2)
#define DOWN_BIT (1 << 3)



typedef struct {
	SemaphoreHandle_t* sems;
	short dir_bits;
} user_input;




void producer_sem(void* pvParameters){
	user_input* value_of_direction = (user_input *)pvParameters;
	SemaphoreHandle_t producer_semaphore = value_of_direction->sems[0];
	SemaphoreHandle_t consumer_semaphore = value_of_direction->sems[1];
	BaseType_t status;
	char c;
	while(1)
	{

		status = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Failed to acquire consumer_semaphore\r\n");
			while (1);
		}

		SCANF("%c", &c);
		switch(c)
		{
		case 'a':
			value_of_direction->dir_bits = LEFT_BIT;
			break;
		case 's':
			value_of_direction->dir_bits = DOWN_BIT;
			break;
		case 'd':
			value_of_direction->dir_bits = RIGHT_BIT;
			break;
		case 'w':
			value_of_direction->dir_bits = UP_BIT;
			break;
		}

		xSemaphoreGive(producer_semaphore);
	}
}

void dir_consumer_sem(void* pvParameters){
	user_input* value_of_direction = (user_input *)pvParameters;
	SemaphoreHandle_t producer_semaphore = value_of_direction->sems[0];
	SemaphoreHandle_t consumer_semaphore = value_of_direction->sems[1];
	BaseType_t status;
	short bits;

	xSemaphoreGive(consumer_semaphore);

	while(1)
	{
		status = xSemaphoreTake(producer_semaphore, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Failed to acquire producer1_semaphore\r\n");
			while (1);
		}

		bits = value_of_direction->dir_bits;

		if((bits & LEFT_BIT) == LEFT_BIT)
		{
			PRINTF("Left\r\n");
		}
		if((bits & RIGHT_BIT) == RIGHT_BIT)
		{
			PRINTF("Right\r\n");
		}
		if((bits & UP_BIT) == UP_BIT)
		{
			PRINTF("Up\r\n");
		}
		if((bits & DOWN_BIT) == DOWN_BIT)
		{
			PRINTF("Down\r\n");
		}

		xSemaphoreGive(consumer_semaphore);
	}
}

int main(){
	BaseType_t status;
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	// Setup task input
	user_input* taskInput = malloc(sizeof(user_input));

	taskInput->sems = malloc(2*sizeof(SemaphoreHandle_t));
	taskInput->sems[0] = xSemaphoreCreateBinary(); //Producer_sem
	taskInput->sems[1] = xSemaphoreCreateBinary(); //consumer_sem

	status = xTaskCreate(producer_sem, "producer", 200, (void*)taskInput, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}
	status = xTaskCreate(dir_consumer_sem, "consumer", 200, (void*)taskInput, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}
	vTaskStartScheduler();
	while (1)
	{}

	return 0;
}
