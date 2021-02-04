/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_PCI954Driver,
    0xff646f80,0x8def,0x11d2,0x94,0x49,0x00,0x10,0x5a,0x07,0x5f,0x6c);
// {ff646f80-8def-11d2-9449-00105a075f6c}
