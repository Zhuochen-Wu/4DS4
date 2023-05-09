#include "Accelerometer_Component.h"

static fxos_handle_t fxosHandle;
static uint8_t data_scale;

void setupAccelerometerComponent()
{
	setupAccelerometerPins();
	voltageRegulator_enable();
	accelerometer_enable();

	spi_init();


    /*************** Accelerometer Task ***************/
	//Create Accelerometer Task
	int status = xTaskCreate(accelerometerTask, "accelerometerTask", 200, (void*)NULL, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}
}

void setupAccelerometerPins()
{
	//Initialize Accelerometer Pins
	   CLOCK_EnableClock(kCLOCK_PortA);
	    /* Port B Clock Gate Control: Clock enabled */
	 CLOCK_EnableClock(kCLOCK_PortB);


	    PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt2);//MISO
	    PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt2);//MOSI
	    PORT_SetPinMux(PORTB, 11U, kPORT_MuxAlt2);//SCLK
	    PORT_SetPinMux(PORTB, 10U, kPORT_MuxAlt2);//CS

	    PORT_SetPinMux(PORTB, 8U, kPORT_MuxAsGpio);
	    PORT_SetPinMux(PORTA, 25U, kPORT_MuxAsGpio);
}

void voltageRegulator_enable()
{
	//Enable voltage Regulator
	gpio_pin_config_t pin_config = {
			.pinDirection = kGPIO_DigitalOutput,
			.outputLogic = 0U};
		GPIO_PinInit(GPIOB, 8, &pin_config);
		GPIO_PinWrite(GPIOB, 8, 1U);
}

void accelerometer_enable()
{
	//Enable accelerometer
	gpio_pin_config_t pin_config = {
			.pinDirection = kGPIO_DigitalOutput,
			.outputLogic = 0U};
		GPIO_PinInit(GPIOA, 25, &pin_config);
		GPIO_PinWrite(GPIOA, 25, 0U);
}

void spi_init()
{
    //Initialize SPI
	dspi_master_config_t masterConfig;
	/* Master config */
	masterConfig.whichCtar = kDSPI_Ctar0;
	masterConfig.ctarConfig.baudRate = 500000;
	masterConfig.ctarConfig.bitsPerFrame = 8U;
	masterConfig.ctarConfig.cpol =
	kDSPI_ClockPolarityActiveHigh;
	masterConfig.ctarConfig.cpha = kDSPI_ClockPhaseFirstEdge;
	masterConfig.ctarConfig.direction = kDSPI_MsbFirst;
	masterConfig.ctarConfig.pcsToSckDelayInNanoSec = 1000000000U / 500000;
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec = 1000000000U / 500000;
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / 500000;
	masterConfig.whichPcs = kDSPI_Pcs0;
	masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;
	masterConfig.enableContinuousSCK = false;
	masterConfig.enableRxFifoOverWrite = false;
	masterConfig.enableModifiedTimingFormat = false;
	masterConfig.samplePoint = kDSPI_SckToSin0Clock;
	DSPI_MasterInit(SPI1, &masterConfig, BUS_CLK);
}

status_t SPI_write(uint8_t regAddress, uint8_t value)
{
	dspi_transfer_t masterXfer;
	uint8_t *masterTxData = (uint8_t*)malloc(3);

	masterTxData[0] = regAddress | 0x80; //set the most significant bit
	masterTxData[1] = regAddress & 0x80; //Clear the least significant
	masterTxData[2] = value; //set value

	masterXfer.txData = masterTxData;
	masterXfer.rxData = NULL;
	masterXfer.dataSize = 3;
	masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 |
			kDSPI_MasterPcsContinuous;

	status_t ret = DSPI_MasterTransferBlocking(SPI1, &masterXfer);

	free(masterTxData);

	return ret;

}

status_t SPI_read(uint8_t regAddress, uint8_t *rxBuff, uint8_t rxBuffSize)
{
	dspi_transfer_t masterXfer;
		uint8_t *masterTxData = (uint8_t*)malloc(rxBuffSize + 2);
		uint8_t *masterRxData = (uint8_t*)malloc(rxBuffSize + 2);

		masterTxData[0] = regAddress & 0x7F; //Clear the most significant bit
		masterTxData[1] = regAddress & 0x80; //Clear the least significant 7 bits

		masterXfer.txData = masterTxData;
		masterXfer.rxData = masterRxData;
		masterXfer.dataSize = rxBuffSize + 2;
		masterXfer.configFlags = kDSPI_MasterCtar0 | kDSPI_MasterPcs0 |
		kDSPI_MasterPcsContinuous;

		status_t ret = DSPI_MasterTransferBlocking(SPI1, &masterXfer);
		memcpy(rxBuff, &masterRxData[2], rxBuffSize);

		free(masterTxData);
		free(masterRxData);

		return ret;
}

void accelerometerTask(void* pvParameters)
{
	//Accelerometer task implementation
	fxos_handle_t fxosHandle = {0};
	fxos_data_t sensorData = {0};
	fxos_config_t config = {0};

	uint8_t sensorRange = 0;
	uint8_t dataScale = 0;
	int16_t yData = 0;
	uint8_t i = 0;
	uint8_t array_addr_size = 0;

	status_t result = kStatus_Fail;

	volatile int16_t yAngle = 0;

	/* Configure the SPI function */
	config.SPI_writeFunc = SPI_write;
	config.SPI_readFunc = SPI_read;

	result = FXOS_Init(&fxosHandle, &config);
	if (result != kStatus_Success)
	{
		PRINTF("\r\nSensor device initialize failed!\r\n");
		while(1);
	}

	/* Get sensor range */
	if (FXOS_ReadReg(&fxosHandle, XYZ_DATA_CFG_REG, &sensorRange, 1) != kStatus_Success)
	{
		PRINTF("Failed to get sensor range!.\r\n");
		while(1);
	}

	if (sensorRange == 0x00)
	{
		dataScale = 2U;
	}
	else if (sensorRange == 0x01)
	{
		dataScale = 4U;
	}
	else if (sensorRange == 0x10)
	{
		dataScale = 8U;
	}
	else{

	}
	msg_struct_t compensation = {.type=1,.val=0};
	BaseType_t status;
	while (1)
	{

		/* Get new accelerometer data. */
		if (FXOS_ReadSensorData(&fxosHandle, &sensorData) != kStatus_Success)
		{
			PRINTF("Failed to get data!.\r\n");
			while(1);
		}
		/* Get the X and Y data from the sensor data structure in 14 bit left format data*/

		yData = ((int16_t)((uint16_t)((uint16_t)sensorData.accelXMSB << 8) | (uint16_t)	sensorData.accelXLSB)) / 4U;
		/* Convert raw data to angle (normalize to -45 -> 45 degrees). No negative angles. */
		yAngle = ((int16_t)((double)yData * (double)dataScale * 90 / 8192) >> 1);
		compensation.val = yAngle;
//		PRINTF("angle value = %d\r\n", yAngle);
		if(abs(yAngle) > 2){
			status = xQueueSendToBack(motor_queue, (void *) &compensation, portMAX_DELAY);
			if (status != pdPASS)
			{
				PRINTF("Queue Send failed!.\r\n");
				while (1);
			}
//			PRINTF("angle value = %d\r\n", yAngle);
			sendMessage("tile angle= %d\r\n", yAngle);
		}else{
			vTaskDelay(100/portTICK_PERIOD_MS);
		}
	}


}
