#include <stdio.h>
#include <stdlib.h>


#include "..\libftd2xx\ftd2xx.h"

// 아래의 i2c나 spi 둘 중 하나만 include해야 함
#include "..\include\libmpsse_i2c.h"
//#include "..\include\libmpsse_spi.h"

FT_STATUS status;

int main(void)
{

	DWORD verMPSSE, verD2XX;

	status = Ver_libMPSSE(&verMPSSE, &verD2XX);
	printf("libmpsse: %08x\n", verMPSSE);
	printf("libftd2xx: %08x\n", verD2XX);
}