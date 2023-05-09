#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/debug_value.h>
#include <math.h>


#define DC_MOTOR 0
#define SERVO_MOTOR 1


extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

void motor_input(test_motor_s *, float);
void servo_input(test_motor_s *, float);

int hello_world_main(int argc, char *argv[])
{	
	px4_sleep(2);	
	debug_value_s debug_data;
	int debug_handle = orb_subscribe(ORB_ID(debug_value));
	orb_set_interval(debug_handle, 500);

	// Motor & LED Configuration
	test_motor_s test_motor;
	test_motor_s test_servo;
	float motor_val_init = 0.6;
	float motor_value = 0.5; // a number between 0 to 1
	float servo_value = 0.5;

	uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));
	uORB::Publication<test_motor_s> test_servo_pub(ORB_ID(test_motor));

	//center the motor and servo at the beginning
	motor_input(&test_motor, motor_value);
	servo_input(&test_servo, servo_value);

	test_motor_pub.publish(test_motor);
	test_servo_pub.publish(test_servo);
	
	//initialize the motor speed to 0.6
	motor_input(&test_motor, motor_val_init);
	test_motor_pub.publish(test_motor);




	while (1) {
		orb_copy(ORB_ID(debug_value), debug_handle, &debug_data);
		// Angle Control

		if (debug_data.value < 30 && debug_data.value >5) {
			motor_value = motor_val_init - (motor_val_init-0.5f)*((30.0f-debug_data.value)/30.0f);

		} else if (debug_data.value <= 5) {
			motor_value = 0.5;
		}else{
			motor_value = motor_val_init;
		}


		if (debug_data.ind == 0)
		{
			servo_value = 0.8;
		}
		else if (debug_data.ind == 1) {
			servo_value = 0.5;
		}
		else if (debug_data.ind == 2) {
			servo_value = 0.3;
		}

		motor_input(&test_motor, motor_value);
		servo_input(&test_servo, servo_value);

		test_motor_pub.publish(test_motor);
		test_servo_pub.publish(test_servo);
		px4_usleep(200000);
	}

	return 0;
}

void motor_input(test_motor_s *test_motor, float motor_value)
{
	test_motor->timestamp = hrt_absolute_time();
	test_motor->motor_number = DC_MOTOR;
	test_motor->value = motor_value;
	test_motor->action = test_motor_s::ACTION_RUN;
	test_motor->driver_instance = 0;
	test_motor->timeout_ms = 0;
}

void servo_input(test_motor_s *test_servo, float servo_value)
{
	test_servo->timestamp = hrt_absolute_time();
	test_servo->motor_number = SERVO_MOTOR;
	test_servo->value = servo_value;
	test_servo->action = test_motor_s::ACTION_RUN;
	test_servo->driver_instance = 0;
	test_servo->timeout_ms = 0;
}


