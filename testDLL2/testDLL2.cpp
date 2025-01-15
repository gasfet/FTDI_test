// testDLL2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include "ftdi_infra.h"		/*Common portable infrastructure(datatypes, libraries, etc)*/
#include "ftdi_common.h"	/*Common across I2C, SPI, JTAG modules*/
#include "ftdi_mid.h"		/*Middle layer*/
#include "libmpsse_i2c.h"	/*I2C specific*/

DWORD channels;
FT_HANDLE ftHandle;
ChannelConfig channelConf;
FT_STATUS status;

int main()
{
	DWORD verMPSSE, verD2XX;
	DWORD channel;
	FT_DEVICE_LIST_INFO_NODE devList;

	Init_libMPSSE();

	printf("\nVersion Check\n");
	status = Ver_libMPSSE(&verMPSSE, &verD2XX);
	printf("libmpsse: %08x\n", verMPSSE);
	printf("libftd2xx: %08x\n", verD2XX);

	printf("\nTest case 1 - I2C_GetNumChannels\n");
	status = I2C_GetNumChannels(&channels);
	printf("		I2C_GetNumChannels returned %d; channels=%d\n", status, channels);


	Cleanup_libMPSSE();

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
