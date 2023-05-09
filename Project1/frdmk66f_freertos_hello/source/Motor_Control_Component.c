#include "Motor_Control_Component.h"

QueueHandle_t motor_queue;
QueueHandle_t angle_queue;

void setupMotorComponent()
{
	BaseType_t status;
	setupMotorPins();
	setupMotors();
	setupServo();

	for(volatile int i = 0U; i < 800000; i++){
    __asm("NOP");
  }


    /*************** Motor Task ***************/
	//Create Motor Queue
	motor_queue = xQueueCreate(5, sizeof(msg_struct_t));

	//Create Motor Task
	status = xTaskCreate(motorTask, "motor", 200, (void*)motor_queue, 2, NULL);
	if (status != pdPASS){
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}

    /*************** Position Task ***************/
	//Create Angle Queue
	angle_queue = xQueueCreate(5, sizeof(int));

	//Create Position Task
	status = xTaskCreate(positionTask, "position", 200, (void*)angle_queue, 2, NULL);
	if (status != pdPASS){
		PRINTF("Task creation failed!.\r\n");
		while (1);
	}
}





// *******************************************************************************************

void setupMotorPins()
{
  // pin_mux.c, BOARD_InitPins
  //Configure PWM pins for DC and Servo motors
	//dc
	CLOCK_EnableClock(kCLOCK_PortC);
	PORT_SetPinMux(PORTC,1U, kPORT_MuxAlt4);

	//servo
	CLOCK_EnableClock(kCLOCK_PortA);
	PORT_SetPinMux(PORTA,6U, kPORT_MuxAlt3);
}


// setupPWM()
void setupMotors()
{
	//Initialize PWM for DC motor
	//lab1_q1 code
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;
	ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;
	ftmParam.chnlNumber = FTM_CHANNEL_DC_MOTOR;
	ftmParam.level = pwmLevel;
	ftmParam.dutyCyclePercent = 7;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;
	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = kFTM_Prescale_Divide_128;
	FTM_Init(FTM_MOTORS, &ftmInfo);
	FTM_SetupPwm(FTM_MOTORS, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50U, CLOCK_GetFreq(
	kCLOCK_BusClk));
	FTM_StartTimer(FTM_MOTORS, kFTM_SystemClock);
}

// setupPWM_SERVO
void setupServo()
{
	//Initialize PWM for Servo motor
	//lab1_q1 code
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;
	ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;
	ftmParam.chnlNumber = FTM_CHANNEL_SERVO;
	ftmParam.level = pwmLevel;
	ftmParam.dutyCyclePercent = 7;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;
	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = kFTM_Prescale_Divide_128;
	FTM_Init(FTM_MOTORS, &ftmInfo);
	FTM_SetupPwm(FTM_MOTORS, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50U, CLOCK_GetFreq(
	kCLOCK_BusClk));
	FTM_StartTimer(FTM_MOTORS, kFTM_SystemClock);
}



// updatePWM_dutyCycle
void updatePWM_dutyCycle(ftm_chnl_t channel, float dutyCycle)
{
	uint32_t cnv, cnvFirstEdge = 0, mod;

	/* The CHANNEL_COUNT macro returns -1 if it cannot match the FTM instance */
	assert(-1 != FSL_FEATURE_FTM_CHANNEL_COUNTn(FTM_MOTORS));
	//sendMessage("Duty cycle =%6.5f\r\n", dutyCycle);
	//sendMessage("channel =%d\r\n", (int)channel);

	mod = FTM_MOTORS->MOD;
	if(dutyCycle == 0U)
	{
		/* Signal stays low */
		cnv = 0;
	}
	else
	{
		cnv = mod * dutyCycle;
		/* For 100% duty cycle */
		if (cnv >= mod)
		{
			cnv = mod + 1U;
		}
	}

	FTM_MOTORS->CONTROLS[channel].CnV = cnv;
}


// *******************************************************************************************




void motorTask(void* pvParameters)
{
	//Motor task implementation
  // queue1 is pvParameters is the fourth argument in xTaskCreate
  // value assigned in pvParameters can be fetched from xQueueSendToBack(void* queue, & value, (Delay))
  // xQueueSendToBack (*void queue) = xTaskCreate(...,...,..., (void* queue)) = xQueueReceive(queue1); queue1 = void* pvParameters

	QueueHandle_t queue1 = (QueueHandle_t)pvParameters;
	BaseType_t status;
	msg_struct_t motor_struct;
	int prev_value;

  // record the previous speed to see if it needs to change
  int prev_speed = 0;
	float dutyCycle;
	prev_value = 0;

	while(1)
	{
		status = xQueueReceive(queue1, (void *) &motor_struct, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Queue Receive failed!.\r\n");
			while (1);
		}

//**********************************************************************************************************************
		if(motor_struct.mode == -1){ // if motor command comes from terminal - keep previous mode
			motor_struct.mode = prev_speed; // the same speed slot with the previous one
		} else {
			prev_speed = motor_struct.mode;
		}
//**********************************************************************************************************************



    // normal
		if(motor_struct.type == 0 && motor_struct.val != prev_value){ // difference in speed

			dutyCycle = (motor_struct.mode + 1) * (float)(motor_struct.val)/3.0f * 0.025f/100.0f + 0.069f;
			updatePWM_dutyCycle(FTM_CHANNEL_DC_MOTOR, dutyCycle);
			sendMessage("motor value = %d\r\n", (motor_struct.mode + 1) * (motor_struct.val) / 3);
			FTM_SetSoftwareTrigger(FTM_MOTORS, true);
			prev_value = motor_struct.val;
      } else if (motor_struct.type == 1 && motor_struct.val<=100 && motor_struct.val>=-100) { //compensation


      int compensated_val = prev_value - motor_struct.val;
			// clip values
			if (compensated_val<-100) {
				compensated_val = -100;
				printf("MAXED OUT\r\n");
			}
			else if (compensated_val > 100){
				compensated_val = 100;
				printf("MAXED OUT\r\n");
			}
			else if (prev_value>0 && compensated_val<0) {
				compensated_val = 0;
				printf("MIN'd OUT\r\n");
			}
			else if (prev_value<0 && compensated_val>0) {
				compensated_val = 0;
				printf("MIN'd OUT\r\n");
			}

			dutyCycle = (motor_struct.mode + 1) * (float)(compensated_val)/3.0f * 0.025f/100.0f + 0.0705f;
			updatePWM_dutyCycle(FTM_CHANNEL_DC_MOTOR, dutyCycle);

      //PRINTF("COMPENSATING: %d\r\n", motor_struct.val);
      //PRINTF("Motor Value = %d\r\n", compensated_val);
			//sendMessage("motor compensation = %d\r\n", compensated_val);
			FTM_SetSoftwareTrigger(FTM_MOTORS, true);
			vTaskDelay(10/portTICK_PERIOD_MS);
		}
		vTaskDelay(1);
	}
}

void positionTask(void* pvParameters)
{

	QueueHandle_t queue1 = (QueueHandle_t)pvParameters;
	BaseType_t status;
	float dutyCycle;

  // new input
  int angle_value;

  // record the value from the previous rotation
	int prev_value = 0;

  // queue1 is pvParameters is the fourth argument in xTaskCreate
  // value assigned in pvParameters can be fetched from xQueueSendToBack(void* queue, & value, (Delay))
  // xQueueSendToBack (*void queue) = xTaskCreate(...,...,..., (void* queue)) = xQueueReceive(queue1); queue1 = void* pvParameters
	while(1)
	{
		status = xQueueReceive(queue1, (void *) &angle_value, portMAX_DELAY);

    // exceptions
		if (status != pdPASS){
			PRINTF("Queue Receive failed!.\r\n");
			while (1);
		}

    // servo main{}
		if(angle_value != prev_value){
			dutyCycle = angle_value * 0.025f/100.0f + 0.075;
			updatePWM_dutyCycle(FTM_CHANNEL_SERVO, dutyCycle);
			sendMessage("Servo angle =%d\r\n", angle_value);
			FTM_SetSoftwareTrigger(FTM_MOTORS, true);
			prev_value = angle_value;
		}
		vTaskDelay(1);
	}
}
