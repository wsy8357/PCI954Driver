/*++

Module Name:

    device.h

Abstract:

    This file contains the device definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#include "public.h"
#include "GPIOCtl.h"

EXTERN_C_START

//window Nt 内核下使用的名称 设备文件名称
#define GPD_DEVICE_NAME L"\\Device\\3U24"

//window Dos内核下使用的名称 设备文件名称
#define DOS_DEVICE_NAME L"\\DDosDevices\\3U24Dev"

#define COM_NUM         4

//定义PCI设备生产商ID、产品ID
#define PCI_954_VID 0x10B5
#define PCI_954_DID 0x9052

//
// The device context performs the same job as
// a WDM device extension in the driver frameworks
//
typedef struct _DEVICE_CONTEXT
{
    //TODO
    ULONG PrivateDeviceData;  // just a placeholder

    PUNICODE_STRING RegistryPath;
    PVOID           PortBase;
    ULONG           PortCount;
    ULONG           PortMemoryType;
    PDEVICE_OBJECT  DeviceObject;
    PDEVICE_OBJECT  NextLowerDriver;
    BOOLEAN         Started;
    BOOLEAN         Removed;
    BOOLEAN         PortWasMapped;
    IO_REMOVE_LOCK  RemoveLock;

    //与中断相关
    PKINTERRUPT     InterruptObject;
    BOOLEAN         FoundInterrupt;
    KIRQL           InterruptLevel;
    ULONG           InterruptVector;
    KAFFINITY       InterruptAffinity;
    KINTERRUPT_MODE InterruptMode;
    ULONG           TestIsr;
    //结束

    //与PCI相关 
    ULONG           BusNumber;
    PCI_SLOT_NUMBER SlotNumber;
    //结束

    //与收发相关的变量
    PVOID           ComBase[COM_NUM];
    
    COM_SET_MODE    ComState[COM_NUM];
    BOOLEAN         Inited[COM_NUM];
    
    KSEMAPHORE      BufSemaphore[2][COM_NUM];
    PVOID           BufBase[2][COM_NUM];
    PVOID           DataNumBase[2][COM_NUM];
    PVOID           PtrBuff[2][COM_NUM];
    //结束
} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

//
// This macro will generate an inline function called DeviceGetContext
// which will be used to get a pointer to the device context memory
// in a type safe manner.
//
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

//
// Function to initialize the device and its callbacks
//
NTSTATUS
PCI954DriverCreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
    );

EXTERN_C_END
