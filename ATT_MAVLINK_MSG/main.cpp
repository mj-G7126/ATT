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

void handleMessage(fmav_message_t* msg, int tmp, uint32_t _boot_ms)
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
			100000+tmp * 1e5,	//alt
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
			_boot_ms,			//time_boot_ms
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

int main(int argc, _TCHAR* argv[])
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("COM9");    // 컴포트 수정은 여기서

	if (SP->IsConnected())
		printf("We're connected");

	int readResult = 0;
	int dTmp = 0;
	int dTmp2 = 1;
	uint32_t boot_ms = 0;
	while (SP->IsConnected())
	{
		clock_t time = clock();
		boot_ms = (uint32_t)time;
		

		if (dTmp < -10) dTmp2 = 1;
		else if (dTmp > 10) dTmp2 = -1;
		dTmp += dTmp2;

		msg.msgid = FASTMAVLINK_MSG_ID_GPS_RAW_INT;
		handleMessage(&msg, dTmp,boot_ms);
		dataLength = fmav_msg_to_frame_buf(tx_buf, &msg);
		tx_buf_char = (char*)tx_buf;
		SP->WriteData(tx_buf_char, dataLength);

		msg.msgid = FASTMAVLINK_MSG_ID_GLOBAL_POSITION_INT;
		handleMessage(&msg, dTmp,boot_ms);
		dataLength = fmav_msg_to_frame_buf(tx_buf, &msg);
		tx_buf_char = (char*)tx_buf;
		SP->WriteData(tx_buf_char, dataLength);

	}
	return 0;
}