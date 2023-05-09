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
			PX4_INFO("ch %d: %f", i, (double)sensor_data.channels[i]);
		}
		PX4_INFO("\n");

		px4_usleep(200000);
	}
return 0;
}
