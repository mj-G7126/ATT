
#include "main.h"	

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
		msg.msgid = FASTMAVLINK_MSG_ID_GPS_RAW_INT;
		handleMessage(&msg);
		dataLength = fmav_msg_to_frame_buf(tx_buf, &msg);
		tx_buf_char = (char*)tx_buf;
		SP->WriteData(tx_buf_char, dataLength);

		msg.msgid = FASTMAVLINK_MSG_ID_GLOBAL_POSITION_INT;
		handleMessage(&msg);
		dataLength = fmav_msg_to_frame_buf(tx_buf, &msg);
		tx_buf_char = (char*)tx_buf;
		SP->WriteData(tx_buf_char, dataLength);

	}
	return 0;
}