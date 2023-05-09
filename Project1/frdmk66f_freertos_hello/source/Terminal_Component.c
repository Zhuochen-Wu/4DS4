#include "Terminal_Component.h"

EventGroupHandle_t event_group;
QueueHandle_t uart_queue;
TimerHandle_t timer_handle;
void timerCallbackFunction(TimerHandle_t timer_handle) {
	BaseType_t status;
	int val_to_send = 0;
	msg_struct_t motor_msg = {.type=0, .val=val_to_send};
	status = xQueueSendToBack(angle_queue,(void*)&val_to_send,portMAX_DELAY);
	if (status != pdPASS)
	{
		PRINTF("QueueSend failed!.\r\n");
		while (1);
	}
	status = xQueueSendToBack(motor_queue,(void*)&motor_msg,portMAX_DELAY);
	if (status != pdPASS)
	{
		PRINTF("QueueSend failed!.\r\n");
		while (1);
	}
	xSemaphoreGive(*rc_hold_semaphore);
}
void setupTerminalComponent()
{
	BaseType_t status;

	setupTerminalPins();

	setupUART();

    /*************** UART Task ***************/
	uart_queue = xQueueCreate(10, sizeof(char*));
	if (uart_queue == NULL)
	{
		PRINTF("Queue creation failed!.\r\n");
		while (1);
	}
    status = xTaskCreate(uartTask, "UART task", 200, NULL, 3, NULL);
    if (status != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1);
    }
    timer_handle = xTimerCreate("Periodic timer", 100/ portTICK_PERIOD_MS, pdFALSE, (void*)0, timerCallbackFunction);


    /*************** Terminal Control Task ***************/
    //Create Event groups
    event_group = xEventGroupCreate();
	//Create Terminal Control Task
	status = xTaskCreate(terminalControlTask, "terminalControlTask", 200, (void*)event_group, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}
}

void setupTerminalPins()
{
    //Configure UART pins
	CLOCK_EnableClock(kCLOCK_PortC);
	PORT_SetPinMux(PORTC, 14U, kPORT_MuxAlt3);
	PORT_SetPinMux(PORTC, 13U, kPORT_MuxAlt3);
	PORT_SetPinMux(PORTC, 15U, kPORT_MuxAlt3);
	CLOCK_EnableClock(kCLOCK_PortE);
	PORT_SetPinMux(PORTE, 27U, kPORT_MuxAlt3);
}

void sendMessage(const char *format, ...)
{
	va_list args;

	char* str = (char*)pvPortMalloc(250 * sizeof(char));

	va_start(args, format);
	vsprintf(str, format, args);

	if(xQueueSendToBack(uart_queue, (void *) &str, portMAX_DELAY) != pdPASS )
	{
		PRINTF("Send message to uart_queue failed!.\r\n");
		while (1);
	}

	va_end(args);
}

void setupUART()
{
	//Setup UART for sending and receiving
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

void uartTask(void* pvParameters)
{
	char* welcome_message = "UART task started\n\r";
	char* received_str;
	BaseType_t status;

	UART_WriteBlocking(TARGET_UART, welcome_message, strlen(welcome_message));

	while(1)
	{
		status = xQueueReceive(uart_queue, (void *) &received_str, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Queue Send failed!.\r\n");
			while (1);
		}
		UART_WriteBlocking(TARGET_UART, received_str, strlen(received_str));
		vPortFree(received_str);
	}
}

void UART4_RX_TX_IRQHandler()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		UART_GetStatusFlags(TARGET_UART);

		char ch = UART_ReadByte(TARGET_UART);
		switch (ch) {
			case 'a':
				xEventGroupSetBitsFromISR(event_group, LEFT_BIT, &xHigherPriorityTaskWoken);
			break;
			case 's':
				xEventGroupSetBitsFromISR(event_group, DOWN_BIT, &xHigherPriorityTaskWoken);
			break;
			case 'd':
				xEventGroupSetBitsFromISR(event_group, RIGHT_BIT, &xHigherPriorityTaskWoken);
			break;
			case 'w':
				xEventGroupSetBitsFromISR(event_group, UP_BIT, &xHigherPriorityTaskWoken);
			break;
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


void terminalControlTask(void* pvParameters)
{
	//Terminal Control Task implementation
	EventGroupHandle_t event_group = (EventGroupHandle_t) pvParameters;
	EventBits_t bits;
	BaseType_t status;
	int val_to_send;
	msg_struct_t motor_msg;
	motor_msg.type = 0;
	motor_msg.mode = -1;
	while (1) {
		bits = xEventGroupWaitBits(event_group, LEFT_BIT | RIGHT_BIT | UP_BIT | DOWN_BIT, pdTRUE, pdFALSE,	portMAX_DELAY);

		if(xTimerIsTimerActive(timer_handle) == pdFALSE){
			status = xSemaphoreTake(*rc_hold_semaphore,portMAX_DELAY);
				if (status != pdPASS)
				{
					PRINTF("Couldn't take hold semaphore!.\r\n");
					while (1);
				}
		}

		status = xTimerReset(timer_handle,portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("timer failed to start!.\r\n");
			while (1);
		}


		if ((bits & LEFT_BIT) == LEFT_BIT) {
			PRINTF("Left\r\n");
			val_to_send = 100;
			status = xQueueSendToBack(angle_queue,(void*)&val_to_send,portMAX_DELAY);
			if (status != pdPASS)
			{
				PRINTF("QueueSend failed!.\r\n");
				while (1);
			}
		}
		if ((bits & RIGHT_BIT) == RIGHT_BIT) {
			PRINTF("Right\r\n");
			val_to_send = -100;
			status = xQueueSendToBack(angle_queue,(void*)&val_to_send,portMAX_DELAY);
			if (status != pdPASS)
			{
				PRINTF("QueueSend failed!.\r\n");
				while (1);
			}
		}
		if ((bits & UP_BIT) == UP_BIT) {
			PRINTF("Up\r\n");
			val_to_send = 100;
			motor_msg.val = val_to_send;
			status = xQueueSendToBack(motor_queue,(void*)&motor_msg,portMAX_DELAY);
			if (status != pdPASS)
			{
				PRINTF("QueueSend failed!.\r\n");
				while (1);
			}
		}
		if ((bits & DOWN_BIT) == DOWN_BIT) {
			PRINTF("Down\r\n");
			val_to_send = -100;
			motor_msg.val = val_to_send;
			status = xQueueSendToBack(motor_queue,(void*)&motor_msg,portMAX_DELAY);
			if (status != pdPASS)
			{
				PRINTF("QueueSend failed!.\r\n");
				while (1);
			}
		}

	}

}
