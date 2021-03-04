#include "deviceCtrl.h"
#include "Driver.h"

#include "deviceCtrl.tmh"



NTSTATUS
WriteSwitch(
	_In_ WDFDEVICE deviceObject,
	_In_ PVOID buffer,
	_In_	size_t len
)
{
	PDEVICE_CONTEXT device_info;
	UCHAR data1=0;
	UCHAR data2=0;

	device_info = DeviceGetContext(deviceObject);

	if(len<2)
	{
		//事件记录 缓存区有效长度小于预计有效长度
		TraceEvents(TRACE_LEVEL_WARNING, TRACE_DEVICECTRL, "%!FUNC! Param 3 len < 2");

		return STATUS_GHOSTED;
	}

	if (FALSE == device_info->findPortSpace)
	{
		TraceEvents(TRACE_LEVEL_WARNING, TRACE_DEVICECTRL, "%!FUNC! driver unfound Port Space!");

		return STATUS_UNSUCCESSFUL;
	}

	data1 = *((PUCHAR)buffer);
	data2 = *((PUCHAR)buffer+1);

	WRITE_PORT_UCHAR((PUCHAR)((ULONG_PTR)device_info->PortBase + 0x263), data1);

	WRITE_PORT_UCHAR((PUCHAR)((ULONG_PTR)device_info->PortBase + 0x264), data2);

	return STATUS_SUCCESS;
}
