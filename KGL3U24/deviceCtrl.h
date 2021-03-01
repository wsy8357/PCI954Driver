#pragma once
#include <ntddk.h>
#include <wdf.h>

#include "trace.h"
EXTERN_C_START

/**
* 用于处理 PCI板卡上的开关量输出
* 
* deviceObject 需要被控制的设备句柄
* 
* buffer		传入的数据缓存区(不要进行Free！)
* 
* len			缓存区有效字节长度
*/
NTSTATUS
WriteSwitch(
	_In_ WDFDEVICE deviceObject,
	_In_ PVOID buffer,
	_In_	size_t len
);

EXTERN_C_END