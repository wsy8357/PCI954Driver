// KGL3U24Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define INITGUID

#include <Windows.h>
#include <SetupAPI.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include <Public.h>

HANDLE hDevice = NULL;
PSP_DEVICE_INTERFACE_DETAIL_DATA pDeviceInterfaceDetail;
HDEVINFO hDevInfo;

BOOL console;

typedef struct {
    uint8_t data1;
    uint8_t data2;
}SWITCH_WRITE_DATA;

bool OpenDevice();
//void WriteSwitch(int index, bool isenable);
bool CloseDevice();
bool GetDevicePath();
int main()
{

    if (!OpenDevice())
    {
        printf("3U24设备打开失败!\r\n");
    }
    else
    {
        printf("3U24设备打开成功!\r\n");
    }

    int deviceResult;

    unsigned long ReturnedLength;

    SWITCH_WRITE_DATA swi;

    swi.data1 = 0xFE;
    swi.data2 = 0xFF;

    printf("打开通道1\r\n");

    deviceResult = DeviceIoControl(hDevice,
        IOCTRL_GPD_WRITE_SWITCH,
        &swi,
        sizeof(SWITCH_WRITE_DATA),
        NULL,
        0,
        &ReturnedLength,
        NULL);

    if (deviceResult == TRUE)
    {
        printf("打开成功\r\n");
    }
    else
    {
        printf("打开失败\r\n");
    }

    system("Pause");

    if (!CloseDevice())
    {
        printf("设备关闭失败\r\n");
    }
    else
    {
        printf("设备关闭成功\r\n");
    }

    system("Pause");
    exit(1);
}

bool OpenDevice()
{

    //PCHAR DevicePath;
    BOOL status = TRUE;

    if (pDeviceInterfaceDetail == NULL) {
        status = GetDevicePath();
    }
    if (pDeviceInterfaceDetail == NULL) {
        status = FALSE;
    }

    if (status) {
        hDevice = CreateFile(pDeviceInterfaceDetail->DevicePath,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);
    }


    if (hDevice == INVALID_HANDLE_VALUE) {
        status = FALSE;
        printf("CreateFile failed.  Error:%u", GetLastError());
    }

    return status;
}

bool CloseDevice()
{
    if(CloseHandle(hDevice))
    {
        hDevice = NULL;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool GetDevicePath()
{
    SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
    SP_DEVINFO_DATA DeviceInfoData;

    ULONG size;
    int count, i, index;

    BOOL status = TRUE;
    TCHAR* DeviceName = NULL;
    TCHAR* DeviceLocation = NULL;

    //获取PLX 设备信息
    hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_KGL3U24,
        NULL,
        NULL,
        (DIGCF_DEVICEINTERFACE | DIGCF_PRESENT));

    //初始化设备信息结构体
    DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    //获取有多少设备在这个父级
    count = 0;
    while (SetupDiEnumDeviceInterfaces(hDevInfo,
        NULL,
        &GUID_DEVINTERFACE_KGL3U24,
        count++,
        &DeviceInterfaceData));

    count--;

    if (count == 0)
    {
        printf("No PLX device are present and enable in the system\n");

        return FALSE;
    }

    DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    i = 0;
    while (SetupDiEnumDeviceInterfaces(hDevInfo,
        NULL,
        &GUID_DEVINTERFACE_KGL3U24,
        i,
        &DeviceInterfaceData))
    {
        SetupDiGetDeviceInterfaceDetail(hDevInfo,
            &DeviceInterfaceData,
            NULL,
            0,
            &size,
            NULL);

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
            printf("SetupDiGetDeviceInterfaceDetail failed, Error: %u", GetLastError());
            return FALSE;
        }

        pDeviceInterfaceDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(size);

        if (!pDeviceInterfaceDetail)
        {
            printf("Insufficient memory.\n");
            return FALSE;
        }

        pDeviceInterfaceDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        status = SetupDiGetDeviceInterfaceDetail(hDevInfo,
            &DeviceInterfaceData,
            pDeviceInterfaceDetail,
            size,
            NULL,
            &DeviceInfoData);

        free(pDeviceInterfaceDetail);

        if (!status) {
            printf("SetupDiGetDeviceInterfaceDetail failed, Error: %u", GetLastError());
            return status;
        }

        SetupDiGetDeviceRegistryProperty(hDevInfo,
            &DeviceInfoData,
            SPDRP_DEVICEDESC,
            NULL,
            (PBYTE)DeviceName,
            0,
            &size);

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            printf("SetupDiGetDeviceRegistryProperty failed, Error: %u", GetLastError());
            return FALSE;
        }

        DeviceName = (TCHAR*)malloc(size);

        if (!DeviceName)
        {
            printf("Insufficient memory.\n");
            return FALSE;
        }

        status = SetupDiGetDeviceRegistryProperty(hDevInfo,
            &DeviceInfoData,
            SPDRP_DEVICEDESC,
            NULL,
            (PBYTE)DeviceName,
            size,
            NULL);
        if (!status) {
            printf("SetupDiGetDeviceRegistryProperty failed, Error: %u",
                GetLastError());
            free(DeviceName);
            return status;
        }

        //
//  Now retrieve the Device Location.
//
        SetupDiGetDeviceRegistryProperty(hDevInfo,
            &DeviceInfoData,
            SPDRP_LOCATION_INFORMATION,
            NULL,
            (PBYTE)DeviceLocation,
            0,
            &size);

        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            DeviceLocation = (TCHAR*)malloc(size);

            if (DeviceLocation != NULL) {

                status = SetupDiGetDeviceRegistryProperty(hDevInfo,
                    &DeviceInfoData,
                    SPDRP_LOCATION_INFORMATION,
                    NULL,
                    (PBYTE)DeviceLocation,
                    size,
                    NULL);
                if (!status) {
                    free(DeviceLocation);
                    DeviceLocation = NULL;
                }
            }

        }
        else {
            DeviceLocation = NULL;
        }

        if (count > 1 && console) {
            printf_s("%d- ", i);
        }

        printf_s("%ws\n", DeviceName);

        if (DeviceLocation) {
            printf_s("        %ws\n", DeviceLocation);
        }

        free(DeviceName);

        DeviceName = NULL;

        if (DeviceLocation) {
            free(DeviceLocation);
            DeviceLocation = NULL;
        }

        i++;
    }

    index = 0;

    if (count > 1) {
        printf("\nSelect Device: ");

        if (scanf_s("%d", &index) == 0) {
            return FALSE;
        }
    }

    status = SetupDiEnumDeviceInterfaces(hDevInfo,
        NULL,
        &GUID_DEVINTERFACE_KGL3U24,
        index,
        &DeviceInterfaceData);

    if (!status) {
        printf_s("SetupDiEnumDeviceInterfaces failed, Error: %u\n", GetLastError());
        return status;
    }

    SetupDiGetDeviceInterfaceDetail(hDevInfo,
        &DeviceInterfaceData,
        NULL,
        0,
        &size,
        NULL);

    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        printf("SetupDiGetDeviceInterfaceDetail failed, Error: %u\n", GetLastError());
        return FALSE;
    }

    pDeviceInterfaceDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(size);

    if (!pDeviceInterfaceDetail) {
        printf("Insufficient memory.\n");
        return FALSE;
    }

    pDeviceInterfaceDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    status = SetupDiGetDeviceInterfaceDetail(hDevInfo,
        &DeviceInterfaceData,
        pDeviceInterfaceDetail,
        size,
        NULL,
        &DeviceInfoData);

    if (!status) {
        printf("SetupDiGetDeviceInterfaceDetail failed, Error: %u\n", GetLastError());
        return status;
    }

    return status;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
