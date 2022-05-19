#pragma once
#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	
#include <string>
#include "common/mavlink.h"
#include <time.h>

uint8_t my_sysid = 1;
uint8_t my_compid = 10;
uint8_t rx_buf[296];
uint8_t tx_buf[296];
fmav_status_t status;
fmav_message_t msg;

int dataLength = 296;
const char* tx_buf_char;

void handleMessage(fmav_message_t* msg)
{
	switch (msg->msgid)
	{
	case FASTMAVLINK_MSG_ID_GPS_RAW_INT:
	{
		//pack function origin
		//fmav_msg_gps_raw_int_pack(msg, my_sysid, my_compid, 0, 0, 37121456, 12612345, tmp * 1e4, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, &status);

		fmav_gps_raw_int_t payload;
		fmav_msg_gps_raw_int_encode(msg, my_sysid, my_compid, &payload, &status);
		fmav_msg_gps_raw_int_pack(
			msg,
			my_sysid,
			my_compid,
			0,			//time_usec
			0,			//fix_type
			37120000,	//lat
			12612345,	//lon
			100000,	//alt
			0,			//eph
			0,			//epv
			0,			//vel
			0,			//cog
			9,			//satellites_visible
			0,			//alt_ellipsoid
			0,			//h_acc
			0,			//v_acc
			0,			//vel_acc
			0,			//hdg_acc
			0,			//yaw
			&status
		);

	}
	break;

	case FASTMAVLINK_MSG_ID_GLOBAL_POSITION_INT:
	{
		//pack function origin
		//fmav_msg_global_position_int_pack(msg, my_sysid, my_compid, time, 37123456, 12624345, 100, 100, 0, 0, 0, 0, &status);
		fmav_global_position_int_t payload;
		fmav_msg_global_position_int_encode(msg, my_sysid, my_compid, &payload, &status);
		fmav_msg_global_position_int_pack(

			msg,
			my_sysid,
			my_compid,
			0,			//time_boot_ms
			37150000,		//lat
			12612345,		//lon
			100,			//alt
			100,			//relative_alt
			0,				//vx
			0,				//vy
			0,				//vz
			0,				//hdg
			&status
		);

	}
	break;
	}
}