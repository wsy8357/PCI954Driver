/*++

Module Name:

    driver.c

Abstract:

    This file contains the driver entry points and callbacks.

Environment:

    Kernel-mode Driver Framework

--*/

#include "driver.h"
#include "driver.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, KGL3U24EvtDeviceAdd)
#pragma alloc_text (PAGE, KGL3U24EvtDriverContextCleanup)

#pragma alloc_text (PAGE, KGL3U24EvtDevicePrepareHardware)
#pragma alloc_text (PAGE, KGL3U24EvtDeviceReleaseHardware)

#pragma alloc_text (PAGE, KGL3U24EvtDeviceD0Entry)
#pragma alloc_text (PAGE, KGL3U24EvtDeviceD0Exit)
#endif

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:
    DriverEntry initializes the driver and is the first routine called by the
    system after the driver is loaded. DriverEntry specifies the other entry
    points in the function driver, such as EvtDevice and DriverUnload.

Parameters Description:

    DriverObject - represents the instance of the function driver that is loaded
    into memory. DriverEntry must initialize members of DriverObject before it
    returns to the caller. DriverObject is allocated by the system before the
    driver is loaded, and it is released by the system after the system unloads
    the function driver from memory.

    RegistryPath - represents the driver specific path in the Registry.
    The function driver can use the path to store driver related data between
    reboots. The path does not store hardware instance specific data.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise.

--*/
{
    WDF_DRIVER_CONFIG config;
    NTSTATUS status;
    WDF_OBJECT_ATTRIBUTES attributes;

    //
    // Initialize WPP Tracing
    //
    WPP_INIT_TRACING(DriverObject, RegistryPath);

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    //
    // Register a cleanup callback so that we can call WPP_CLEANUP when
    // the framework driver object is deleted during driver unload.
    //
    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
    attributes.EvtCleanupCallback = KGL3U24EvtDriverContextCleanup;

    WDF_DRIVER_CONFIG_INIT(&config,
                           KGL3U24EvtDeviceAdd
                           );

    status = WdfDriverCreate(DriverObject,
                             RegistryPath,
                             &attributes,
                             &config,
                             WDF_NO_HANDLE
                             );

    if (!NT_SUCCESS(status)) {
        TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER, "WdfDriverCreate failed %!STATUS!", status);
        WPP_CLEANUP(DriverObject);
        return status;
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Exit");

    return status;
}

NTSTATUS
KGL3U24EvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
/*++
Routine Description:

    EvtDeviceAdd is called by the framework in response to AddDevice
    call from the PnP manager. We create and initialize a device object to
    represent a new instance of the device.

Arguments:

    Driver - Handle to a framework driver object created in DriverEntry

    DeviceInit - Pointer to a framework-allocated WDFDEVICE_INIT structure.

Return Value:

    NTSTATUS

--*/
{
    NTSTATUS status;
    WDF_PNPPOWER_EVENT_CALLBACKS pnpPowerCallbacks;

    UNREFERENCED_PARAMETER(Driver);

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    WdfDeviceInitSetIoType(DeviceInit, WdfDeviceIoBuffered);

    //初始化PNP事件回调结构体
    WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&pnpPowerCallbacks);

    pnpPowerCallbacks.EvtDevicePrepareHardware = KGL3U24EvtDevicePrepareHardware;
    pnpPowerCallbacks.EvtDeviceReleaseHardware = KGL3U24EvtDeviceReleaseHardware;

    pnpPowerCallbacks.EvtDeviceD0Entry = KGL3U24EvtDeviceD0Entry;
    pnpPowerCallbacks.EvtDeviceD0Exit = KGL3U24EvtDeviceD0Exit;

    //在设备初始化结构体中，设置pnp事件回调结构体
    WdfDeviceInitSetPnpPowerEventCallbacks(DeviceInit, &pnpPowerCallbacks);

    status = KGL3U24CreateDevice(DeviceInit);

    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
            "   KGL3U24CreateDevice filed %!STATUS!", status);
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Exit");

    return status;
}

VOID
KGL3U24EvtDriverContextCleanup(
    _In_ WDFOBJECT DriverObject
    )
/*++
Routine Description:

    Free all the resources allocated in DriverEntry.

Arguments:

    DriverObject - handle to a WDF Driver object.

Return Value:

    VOID.

--*/
{
    UNREFERENCED_PARAMETER(DriverObject);

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    //
    // Stop WPP Tracing
    //
    WPP_CLEANUP(WdfDriverWdmGetDriverObject((WDFDRIVER)DriverObject));
}

NTSTATUS
KGL3U24EvtDevicePrepareHardware(
    _In_
    WDFDEVICE Device,
    _In_
    WDFCMRESLIST ResourcesRaw,
    _In_
    WDFCMRESLIST ResourcesTranslated
)
{
    NTSTATUS            status = STATUS_SUCCESS;
    PDEVICE_CONTEXT     devExt;

    //便利资源使用到的变量
    PCM_PARTIAL_RESOURCE_DESCRIPTOR desc=NULL;
    PHYSICAL_ADDRESS                portStartAddress;
    ULONG                           portLength;

    UNREFERENCED_PARAMETER(ResourcesRaw);

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
        " --> KGL3U24EvtDevicePrepareHardware Entry");

    //获取设备句柄维护的设别信息结构体， 该结构体有设备供应商定义
    devExt = DeviceGetContext(Device);

    //获取PCI配置内容，对地址进行转换映射
    //便利资源列表，保存资源信息
    for (ULONG i = 0; i < WdfCmResourceListGetCount(ResourcesTranslated); i++)
    {
        desc = WdfCmResourceListGetDescriptor(ResourcesTranslated, i);

        if (!desc)
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DRIVER,
                " WdfResourceCmGetDescriptor failed");

            //返回设备配置时错误
            return STATUS_DEVICE_CONFIGURATION_ERROR;
        }

        switch (desc->Type)
        {
            //如果资源类型为端口
        case CmResourceTypePort:
        {
            //在操作 I/O space 时，应当使用 READ_PORT_Xxx 或 WRITE_PORT_Xxx来对端口进行读写操作
            //根据文档描述 这里的地址和长度已经是系统转换好的，并不是PCI总线配置的物理IO端口
            portStartAddress.HighPart = 0;
            portStartAddress.LowPart = desc->u.Port.Start.LowPart;
            portLength = desc->u.Port.Length;

            TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
                "Add: prot I/O starting at 0x%X length 0x%x",
                portStartAddress.LowPart,
                portLength);

            devExt->PortBase = portStartAddress.LowPart;
            devExt->PortCount = portLength;

            devExt->findPortSpace = TRUE;
        }
            break;
        default:
            break;
        }
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER,
        " --> KGL3U24EvtDevicePrepareHardware Exit");

    return status;
}

NTSTATUS KGL3U24EvtDeviceReleaseHardware
(
    WDFDEVICE Device,
    WDFCMRESLIST ResourcesTranslated
)
{
    PDEVICE_CONTEXT     devExt;

    UNREFERENCED_PARAMETER(ResourcesTranslated);

    PAGED_CODE();

    //获取设备句柄维护的设别信息结构体， 该结构体有设备供应商定义
    devExt = DeviceGetContext(Device);

    devExt->PortBase = 0;
    devExt->PortCount = 0;
    devExt->findPortSpace = FALSE;

    return STATUS_SUCCESS;
}

/*
* 当设备电源管理进入活动状态 D0时的事件函数
*/
NTSTATUS KGL3U24EvtDeviceD0Entry
(
    WDFDEVICE Device,
    WDF_POWER_DEVICE_STATE PreviousState
)
{
    PDEVICE_CONTEXT devExt;

    UNREFERENCED_PARAMETER(PreviousState);

    PAGED_CODE();

    devExt = DeviceGetContext(Device);

    devExt->Started = TRUE;
    devExt->Removed = FALSE;

    return STATUS_SUCCESS;
}

NTSTATUS KGL3U24EvtDeviceD0Exit
(
    WDFDEVICE Device,
    WDF_POWER_DEVICE_STATE PreviousState
)
{
    PDEVICE_CONTEXT devExt;

    UNREFERENCED_PARAMETER(PreviousState);

    PAGED_CODE();

    devExt = DeviceGetContext(Device);

    devExt->Started = FALSE;
    devExt->Removed = TRUE;

    return STATUS_SUCCESS;
}