/*
*************************************Experiment 2
#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <uORB/topics/rc_channels.h>

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);
int hello_world_main(int argc, char *argv[])
{
	int rc_channels_handle;
	rc_channels_s sensor_data;
	rc_channels_handle = orb_subscribe(ORB_ID(rc_channels));
	orb_set_interval(rc_channels_handle, 200);
	while(1)
	{
		for(int i=0;i<18;i++){
			orb_copy(ORB_ID(rc_channels), rc_channels_handle, &sensor_data);
			PX4_INFO("ch %d: %f", i+1, (double)sensor_data.channels[i]);
		}
		PX4_INFO("\n");

		px4_usleep(200000);
	}
return 0;
}
*/

#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/led_control.h>
#include <uORB/topics/rc_channels.h>

#define DC_MOTOR 0
#define SERVO_MOTOR 1


extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
	test_motor_s test_motor;
	test_motor_s test_servo;
	led_control_s led_data;
	double motor_value = 0; // a number between 0 to 1
	double servo_value = 0;
	int led_color;

	int rc_channels_handle;
	rc_channels_s sensor_data;
	rc_channels_handle = orb_subscribe(ORB_ID(rc_channels));
	orb_set_interval(rc_channels_handle, 200);












	uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));
	uORB::Publication<test_motor_s> test_servo_pub(ORB_ID(test_motor));
	uORB::Publication<led_control_s> led_control_pub(ORB_ID(led_control));








	//center the motor and servo at the beginning
	test_motor.timestamp = hrt_absolute_time();
	test_motor.motor_number = DC_MOTOR;
	test_motor.value = (float)0.5;
	test_motor.action = test_motor_s::ACTION_RUN;
	test_motor.driver_instance = 0;
	test_motor.timeout_ms = 0;

	test_servo.timestamp = hrt_absolute_time();
	test_servo.motor_number = SERVO_MOTOR;
	test_servo.value = (float)0.5;
	test_servo.action = test_motor_s::ACTION_RUN;
	test_servo.driver_instance = 0;
	test_servo.timeout_ms = 0;

	led_data.timestamp = hrt_absolute_time();
	led_data.led_mask = 0xFF;
	led_data.color = 0;
	led_data.mode = 1;
	led_data.num_blinks = 0;
	led_data.priority = 2;

	test_motor_pub.publish(test_motor);
	test_servo_pub.publish(test_servo);
	led_control_pub.publish(led_data);

	while(1)
	{
		for(int i=0;i<18;i++){
			orb_copy(ORB_ID(rc_channels), rc_channels_handle, &sensor_data);
			PX4_INFO("ch %d: %f", i+1, (double)sensor_data.channels[i]);

		}

		//PX4_INFO("Enter LED color from 0 to 8.\r\n");
		//scanf("%d", &led_color);
		led_color = (double)sensor_data.channels[7] + 2;
		if(led_color > 8 || led_color < 0) break;

		//PX4_INFO("Enter speed value (0 to 1). If you enter a value outside the range, the motor will be stopped and the application will be terminated.");
		//scanf("%lf", &motor_value); // 0.5(+-)0.5/3*3
		//(sensor_data.channels[7] + 2)/9
		if ((double)sensor_data.channels[7] > 0.7){ // high speed mode
			motor_value = 0.5 + (double)sensor_data.channels[2]/2;
		} else if ((double)sensor_data.channels[7] < -0.7){ // low speed mode
			motor_value = 0.5 + (double)sensor_data.channels[2]/6;
		} else{ // medium speed mode
			motor_value = 0.5 + (double)sensor_data.channels[2]/3;
		}
		//motor_value = (((double)sensor_data.channels[2]+1)/2);
		if(motor_value > 1.0 || motor_value < 0)
			break;

		//PX4_INFO("Enter servo value (0 to 1). If you enter a value outside the range, the servo will be stopped and the application will be terminated.");
		//scanf("%lf", &servo_value);
		servo_value = ((double)sensor_data.channels[1]+1)/2;
		if(servo_value > 1.0 || servo_value < 0)
			break;

		if((double)sensor_data.channels[5]>0) break;

		PX4_INFO("Motor speed is %f", motor_value);
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = DC_MOTOR;
		test_motor.value = (float)motor_value;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;

		PX4_INFO("Servo Value is %f", servo_value);
		test_servo.timestamp = hrt_absolute_time();
		test_servo.motor_number = SERVO_MOTOR;
		test_servo.value = (float)servo_value;
		test_servo.action = test_motor_s::ACTION_RUN;
		test_servo.driver_instance = 0;
		test_servo.timeout_ms = 0;

		led_data.timestamp = hrt_absolute_time();
		led_data.led_mask = 0xFF;
		led_data.color = led_color;
		led_data.mode = 1;
		led_data.num_blinks = 0;
		led_data.priority = 2;


		test_motor_pub.publish(test_motor);
		test_servo_pub.publish(test_servo);
		led_control_pub.publish(led_data);

		px4_usleep(50000);
	}

	PX4_INFO("The motor will be stopped");
	test_motor.timestamp = hrt_absolute_time();
	test_motor.motor_number = DC_MOTOR;
	test_motor.value = (float)0.5;
	test_motor.action = test_motor_s::ACTION_RUN;
	test_motor.driver_instance = 0;
	test_motor.timeout_ms = 0;

	PX4_INFO("The servo will be stopped");
	test_servo.timestamp = hrt_absolute_time();
	test_servo.motor_number = SERVO_MOTOR;
	test_servo.value = (float)0.5;
	test_servo.action = test_motor_s::ACTION_RUN;
	test_servo.driver_instance = 0;
	test_servo.timeout_ms = 0;

	led_data.timestamp = hrt_absolute_time();
	led_data.led_mask = 0xFF;
	led_data.color = 0;
	led_data.mode = 1;
	led_data.num_blinks = 0;
	led_data.priority = 2;

	test_motor_pub.publish(test_motor);
	test_servo_pub.publish(test_servo);
	led_control_pub.publish(led_data);

	return 0;
}




















