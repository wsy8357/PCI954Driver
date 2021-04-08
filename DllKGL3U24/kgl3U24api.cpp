#include "pch.h"
#include "kgl3U24api.h"

#include <Public.h>


HANDLE kgl3u24_open()
{
	HANDLE hDevice = CreateFile(USER_DEVICE_NAME,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);


	return hDevice;
}

BOOL kgl3u24_close(HANDLE deviceHandle)
{
	if (deviceHandle == INVALID_HANDLE_VALUE || deviceHandle == NULL)
	{
		return FALSE;
	}

	if (CloseHandle(deviceHandle))
	{
		return TRUE;
	}


	return FALSE;
}

BOOL kgl3u24_output_set(HANDLE deviceHandle, UINT16 param)
{
	SWITCH_WRITE_DATA swi;
	BOOL deviceCtlResult = FALSE;
	unsigned long returnedLength;

	if (deviceHandle == INVALID_HANDLE_VALUE || deviceHandle == NULL)
	{
		return FALSE;
	}

	swi.data1 = ~(UINT8)(param & 0x00FF);
	swi.data2 = ~(UINT8)((param >> 8) & 0x00FF);

	deviceCtlResult = DeviceIoControl(deviceHandle,
		IOCTRL_GPD_WRITE_SWITCH,
		&swi,
		sizeof(SWITCH_WRITE_DATA),
		NULL,
		0,
		&returnedLength,
		NULL);
	
	return deviceCtlResult;
}
