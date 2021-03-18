/*++

Module Name:

    device.h

Abstract:

    This file contains the device definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#include "public.h"

EXTERN_C_START

//Windows NT内核下操作系统使用的设备文件名称
#define GPD_DEVICE_NAME L"\\Device\\3U24"

//windows Dos内核下使用的设备文件名
#define DOS_DEVICE_NAME L"\\DosDevices\\3U24Dev"

//定义设备使用的PCI设备的ID
#define PCI_954_VID 0x10B5
#define PCI_954_DID 0x9052

#define IO_PORT_LENGTH 0x1000

//
// The device context performs the same job as
// a WDM device extension in the driver frameworks
//
typedef struct _DEVICE_CONTEXT
{
    ULONG PrivateDeviceData;  // just a placeholder

    BOOLEAN findPortSpace;  //the true for found a I/O port Space
    ULONG PortBase;         //base port address pointer
    ULONG PortCount;        //Count of I/O address used
    ULONG PortMemoryType;   //HalTranslateBusAddress MemoryType
    PDEVICE_OBJECT  DeviceObject;   //The Gpd device Object
    PDEVICE_OBJECT  NextLowerDriver;    //The Top of stack
    BOOLEAN         Started;
    BOOLEAN         Removed;
    BOOLEAN         PortWasMapped;      //If true, we have to unmap on unload
    BOOLEAN         Filler[1];          //bug fix
    IO_REMOVE_LOCK  RemoveLock;



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
KGL3U24CreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
    );

EXTERN_C_END
