#ifndef MOTOR_CONTROL_COMPONENT_H
#define MOTOR_CONTROL_COMPONENT_H

#include "pin_mux.h"
#include "fsl_port.h"
#include "fsl_ftm.h"
#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Terminal_Component.h"

#define FTM_MOTORS 				FTM0
#define FTM_CHANNEL_DC_MOTOR	kFTM_Chnl_0//Define DC motor channel
#define FTM_CHANNEL_SERVO		kFTM_Chnl_3//Define servo PWM channel

#define SPEED_FAST			70
#define SPEED_SLOW			30

extern QueueHandle_t motor_queue, angle_queue;

typedef struct {
	int type; // 0-speed, 1-compensation
	int mode;
	int val;
} msg_struct_t ;

void setupMotorComponent();
void setupMotors();
void setupServo();
void setupMotorPins();

void updatePWM_dutyCycle(ftm_chnl_t channel, float dutyCycle);
void updateServoPWM_dutyCycle(ftm_chnl_t channel, float dutyCycle);

void motorTask(void* pvParameters);
void positionTask(void* pvParameters);


#endif /* MOTOR_CONTROL_COMPONENT_H */
