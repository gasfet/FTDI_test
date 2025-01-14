#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32
#include <dlfcn.h>
#endif

#include "ftd2xx.h"
#include "libmpsse_i2c.h"

#define APP_CHECK_STATUS(exp) {if (exp != FT_OK) { printf("status(0x%x) != FT_OK\n", exp); } else { ; }}

#define I2C_DEVICE_ADDRESS_RTC          0x50
#define I2C_DEVICE_ADDRESS_EEPROM       0x57
#define I2C_DEVICE_BUFFER_SIZE          256
#define I2C_WRITE_COMPLETION_RETRY      10

#define START_ADDRESS_EEPROM            0xFA
#define END_ADDRESS_EEPROM              0xFC
#define RETRY_COUNT_EEPROM              10

#ifdef DYNAMIC_TEST

#ifdef _WIN32
HANDLE hdll_mpsse;
#else
void* hdll_mpsse;
#endif

FT_STATUS(*I2C_GetNumChannels)(DWORD* numChannels);
FT_STATUS(*I2C_GetChannelInfo)(DWORD index, FT_DEVICE_LIST_INFO_NODE* chanInfo);
FT_STATUS(*I2C_OpenChannel)(DWORD index, FT_HANDLE* handle);
FT_STATUS(*I2C_CloseChannel)(FT_HANDLE handle);
FT_STATUS(*I2C_InitChannel)(FT_HANDLE handle, ChannelConfig* config);
FT_STATUS(*I2C_DeviceRead)(FT_HANDLE handle, DWORD deviceAddress, DWORD bytesToTransfer, UCHAR* buffer, DWORD* bytesTransfered, DWORD options);
FT_STATUS(*I2C_DeviceWrite)(FT_HANDLE handle, DWORD deviceAddress, DWORD bytesToTransfer, UCHAR* buffer, DWORD* bytesTransfered, DWORD options);
FT_STATUS(*I2C_GetDeviceID)(FT_HANDLE handle, UCHAR deviceAddress, UCHAR* deviceID);
FT_STATUS(*Ver_libMPSSE)(LPDWORD verMPSSE, LPDWORD verD2XX);

#endif // DYNAMIC_TEST

DWORD channels;
FT_HANDLE ftHandle;
ChannelConfig channelConf;
FT_STATUS status;
UCHAR buffer[I2C_DEVICE_BUFFER_SIZE];

DWORD write_byte(UCHAR slaveAddress, UCHAR registerAddress, UCHAR data) {
    DWORD bytesToTransfer = 0;
    DWORD bytesTransfered;
    BOOL writeComplete = 0;
    DWORD retry = 0;

    buffer[bytesToTransfer++] = registerAddress;
    buffer[bytesToTransfer++] = data;
    status = I2C_DeviceWrite(ftHandle, slaveAddress, bytesToTransfer, buffer, &bytesTransfered,
        I2C_TRANSFER_OPTIONS_START_BIT | I2C_TRANSFER_OPTIONS_STOP_BIT);
    APP_CHECK_STATUS(status);

    while ((writeComplete == 0) && (retry < I2C_WRITE_COMPLETION_RETRY)) {
        bytesToTransfer = 0;
        bytesTransfered = 0;
        buffer[bytesToTransfer++] = registerAddress;
        status = I2C_DeviceWrite(ftHandle, slaveAddress, bytesToTransfer, buffer, &bytesTransfered,
            I2C_TRANSFER_OPTIONS_START_BIT | I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);
        if (FT_OK != status) {
            printf("EEPROM write cycle isn't complete\n");
        }
        if (bytesToTransfer == bytesTransfered) {
            writeComplete = 1;
            printf("Write done\n");
        }
        else {
            printf("Retrying...\n");
        }
        retry++;
    }
    return 0;
}

FT_STATUS read_byte(UCHAR slaveAddress, UCHAR registerAddress, UCHAR* data) {
    DWORD bytesToTransfer = 0;
    DWORD bytesTransfered;

    buffer[bytesToTransfer++] = registerAddress;
    status = I2C_DeviceWrite(ftHandle, slaveAddress, bytesToTransfer, buffer, &bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT);
    bytesToTransfer = 1;
    bytesTransfered = 0;
    status |= I2C_DeviceRead(ftHandle, slaveAddress, bytesToTransfer, buffer, &bytesTransfered, I2C_TRANSFER_OPTIONS_START_BIT);
    *data = buffer[0];
    return status;
}

int main(void) {
    DWORD channel;
    FT_DEVICE_LIST_INFO_NODE devList;
    channelConf.ClockRate = I2C_CLOCK_FAST_MODE;
    channelConf.LatencyTimer = 0;
    channelConf.Options = (I2C_TRANSFER_OPTIONS_NO_ADDRESS |
        I2C_TRANSFER_OPTIONS_FAST_TRANSFER_BITS |
        I2C_TRANSFER_OPTIONS_BREAK_ON_NACK);
    DWORD verMPSSE, verD2XX;

#ifdef DYNAMIC_TEST
#ifndef _WIN32
    hdll_mpsse = dlopen("libmpsse.so", RTLD_LAZY);
    if (!hdll_mpsse) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        exit(-1);
    }
#else
    hdll_mpsse = LoadLibrary(L"libMPSSE.dll");
    if (!hdll_mpsse) {
        fprintf(stderr, "LoadLibrary failed 0x%x\n", GetLastError());
        exit(-1);
    }
#endif

    I2C_GetNumChannels = (FT_STATUS(*)(DWORD*))GET_FUNC(hdll_mpsse, "I2C_GetNumChannels");
    I2C_GetChannelInfo = (FT_STATUS(*)(DWORD, FT_DEVICE_LIST_INFO_NODE*))GET_FUNC(hdll_mpsse, "I2C_GetChannelInfo");
    I2C_OpenChannel = (FT_STATUS(*)(DWORD, FT_HANDLE*))GET_FUNC(hdll_mpsse, "I2C_OpenChannel");
    I2C_CloseChannel = (FT_STATUS(*)(FT_HANDLE))GET_FUNC(hdll_mpsse, "I2C_CloseChannel");
    I2C_InitChannel = (FT_STATUS(*)(FT_HANDLE, ChannelConfig*))GET_FUNC(hdll_mpsse, "I2C_InitChannel");
    I2C_DeviceRead = (FT_STATUS(*)(FT_HANDLE, DWORD, DWORD, UCHAR*, DWORD*, DWORD))GET_FUNC(hdll_mpsse, "I2C_DeviceRead");
    I2C_DeviceWrite = (FT_STATUS(*)(FT_HANDLE, DWORD, DWORD, UCHAR*, DWORD*, DWORD))GET_FUNC(hdll_mpsse, "I2C_DeviceWrite");
    Ver_libMPSSE = (FT_STATUS(*)(LPDWORD, LPDWORD))GET_FUNC(hdll_mpsse, "Ver_libMPSSE");
#endif

    status = Ver_libMPSSE(&verMPSSE, &verD2XX);
    printf("libmpsse: %08x\nlibftd2xx: %08x\n", verMPSSE, verD2XX);

    status = I2C_GetNumChannels(&channels);
    printf("I2C_GetNumChannels returned %d; channels=%d\n", status, channels);

    for (channel = 0; channel < channels; channel++) {
        status = I2C_GetChannelInfo(channel, &devList);
        printf("Channel %d: Flags=0x%x, Type=0x%x, ID=0x%x, LocId=0x%x, SerialNumber=%s, Description=%s\n",
            channel, devList.Flags, devList.Type, devList.ID, devList.LocId, devList.SerialNumber, devList.Description);

        status = I2C_OpenChannel(channel, &ftHandle);
        APP_CHECK_STATUS(status);
        status = I2C_InitChannel(ftHandle, &channelConf);

        for (UCHAR address = START_ADDRESS_EEPROM; address < END_ADDRESS_EEPROM; address++) {
            write_byte(I2C_DEVICE_ADDRESS_EEPROM, address, address + 1);
        }

        for (UCHAR address = START_ADDRESS_EEPROM; address < END_ADDRESS_EEPROM; address++) {
            UCHAR data;
            read_byte(I2C_DEVICE_ADDRESS_EEPROM, address, &data);
            printf("Address %d: Data %d\n", address, data);
        }

        status = I2C_CloseChannel(ftHandle);
        APP_CHECK_STATUS(status);
    }

    return 0;
}
