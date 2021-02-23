#include "deviceCtrl.h"
#include "Device.h"

NTSTATUS WriteSwitch(WDFDEVICE deviceObject, PVOID buffer, size_t len)
{
	PDEVICE_CONTEXT device_info;
	UCHAR data1=0;
	UCHAR data2=0;

	device_info = DeviceGetContext(deviceObject);

	if(len<2)
	{
		//事件记录 缓存区有效长度小于预计有效长度


		return STATUS_GHOSTED;
	}

	data1 = *((PUCHAR)buffer);
	data2 = *((PUCHAR)buffer+1);

	WRITE_PORT_UCHAR((PUCHAR)((ULONG_PTR)device_info->PortBase + 0x263),data1);

	WRITE_PORT_UCHAR((PUCHAR)((ULONG_PTR)device_info->PortBase + 0x264), data2);

	return STATUS_SUCCESS;
}
