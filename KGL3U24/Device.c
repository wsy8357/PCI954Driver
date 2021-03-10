/*++

Module Name:

    device.c - Device handling events for example driver.

Abstract:

   This file contains the device entry points and callbacks.
    
Environment:

    Kernel-mode Driver Framework

--*/

#include "driver.h"
#include <ntstrsafe.h>
#include "device.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, KGL3U24CreateDevice)
#endif

NTSTATUS
KGL3U24CreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
/*++

Routine Description:

    Worker routine called to create a device and its software resources.

Arguments:

    DeviceInit - Pointer to an opaque init structure. Memory for this
                    structure will be freed by the framework when the WdfDeviceCreate
                    succeeds. So don't access the structure after that point.

Return Value:

    NTSTATUS

--*/
{
    WDF_OBJECT_ATTRIBUTES deviceAttributes;
    PDEVICE_CONTEXT deviceContext;
    WDFDEVICE device;
    NTSTATUS status;
    //UNICODE_STRING deviceName;
    //DECLARE_CONST_UNICODE_STRING(dosDeviceName, DOS_DEVICE_NAME);

    PAGED_CODE();

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&deviceAttributes, DEVICE_CONTEXT);

    status = WdfDeviceCreate(&DeviceInit, &deviceAttributes, &device);

    if (NT_SUCCESS(status)) {
        //
        // Get a pointer to the device context structure that we just associated
        // with the device object. We define this structure in the device.h
        // header file. DeviceGetContext is an inline function generated by
        // using the WDF_DECLARE_CONTEXT_TYPE_WITH_NAME macro in device.h.
        // This function will do the type checking and return the device context.
        // If you pass a wrong object handle it will return NULL and assert if
        // run under framework verifier mode.
        //
        deviceContext = DeviceGetContext(device);

        //
        // Initialize the context.
        //
        deviceContext->PrivateDeviceData = 0;
        //RtlUnicodeStringInit(&deviceName, DEVICE_NAME);
        //
        // Create a device interface so that applications can find and talk
        // to us.
        //
        status = WdfDeviceCreateDeviceInterface(
            device,
            &GUID_DEVINTERFACE_KGL3U24,
            NULL//&deviceName//&dosDeviceName // ReferenceString
            );

        if (NT_SUCCESS(status)) {
            //
            // Initialize the I/O Package and any Queues
            //
            status = KGL3U24QueueInitialize(device);
            WDFSTRING string;
            NTSTATUS inlineStatus = STATUS_SUCCESS;

            WdfStringCreate(NULL, WDF_NO_OBJECT_ATTRIBUTES, &string);
            inlineStatus=WdfDeviceRetrieveDeviceName(device, string);
            if (NT_SUCCESS(inlineStatus))
            {
                UNICODE_STRING name;

                WdfStringGetUnicodeString(string, &name);

                TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE,
                    "Wdf Device Name: %wZ", &name);
            }
            else
            {
                TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                    "GetDevice Name Error Code = %#X", inlineStatus);
            }

        }

       // status = WdfDeviceCreateSymbolicLink(device, &dosDeviceName);
        /*
        if (!NT_SUCCESS(status))
        {
            TraceEvents(TRACE_LEVEL_ERROR, TRACE_DEVICE,
                "Wdf Device Create Symboloc Link Error!");

        }
        */
    }

    return status;
}
