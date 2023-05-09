#include "LED_Component.h"

QueueHandle_t led_queue;

void setupLEDComponent()
{
	setupLEDPins();

	setupLEDs();

    /*************** LED Task ***************/
	//Create LED Queue
  led_queue = xQueueCreate(1, sizeof(int));


	//Create LED Task
  if (xTaskCreate(ledTask, "LED Task", 128, (void* )led_queue, 2, NULL) != pdPASS){
    PRINTF("LED Task creation failed!.\r\n");
    while (1);
  }



}

void setupLEDPins(){
	//Configure LED pins
  CLOCK_EnableClock(kCLOCK_PortC);
  CLOCK_EnableClock(kCLOCK_PortD);
  // red
  PORT_SetPinMux(PORTD, 1u, kPORT_MuxAlt4);
  // blue
  PORT_SetPinMux(PORTC, 8U, kPORT_MuxAlt3);
  // green
  PORT_SetPinMux(PORTC, 9U, kPORT_MuxAlt3);


}

void setupLEDs()
{
  //lab 0 Problem 5
	//Initialize PWM for the LEDs
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam[3];

	ftmParam[0].chnlNumber = kFTM_Chnl_1;
	ftmParam[1].chnlNumber = kFTM_Chnl_4;
	ftmParam[2].chnlNumber = kFTM_Chnl_5;

	for (int i=0; i<3; i++){
		ftmParam[i].level = kFTM_HighTrue;
		ftmParam[i].dutyCyclePercent = 0;
		ftmParam[i].firstEdgeDelayPercent = 0U;
		ftmParam[i].enableComplementary = false;
		ftmParam[i].enableDeadtime = false;
	}

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, ftmParam, 3U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);






}

void ledTask(void* pvParameters){
	//LED task implementation
	int speed = 0;
  int colour;
	while (1){
		PRINTF("LED update.\r\n");

		switch(speed){
			case 0:
				colour = COLOUR_SLOW;
				break;
			case 1:
				colour = COLOUR_MEDIUM;
				break;
			case 2:
				colour = COLOUR_FAST;
				break;
			default:
				colour = COLOUR_SLOW;
		}

    // mask and percentage calculation
		uint8_t blue  = ((float) (colour & 0x0000FF))        / 0xFF * 100;
		uint8_t green = ((float)((colour & 0x00FF00) >> 8))  / 0xFF * 100;
		uint8_t red   = ((float)((colour & 0xFF0000) >> 16)) / 0xFF * 100;



		FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, red);
		FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_4, kFTM_EdgeAlignedPwm, blue);
		FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_5, kFTM_EdgeAlignedPwm, green);

		FTM_SetSoftwareTrigger(FTM3, true);

		xQueueReceive(led_queue, (void *) (&speed), portMAX_DELAY);
	}
}




