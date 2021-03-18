/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

#define USER_DEVICE_NAME L"\\\\.\\3U24Dev"

//
// Define an Interface Guid so that apps can find the device and talk to it.
//
DEFINE_GUID (GUID_DEVINTERFACE_KGL3U24,
    0x93732ead,0x1daf,0x4d9b,0xbd,0x91,0xb6,0x32,0x48,0x0a,0xd9,0x96);
// {93732ead-1daf-4d9b-bd91-b632480ad996}


#define GPD_TYPE 40000

#define IOCTRL_GPD_WRITE_SWITCH \
    CTL_CODE(GPD_TYPE, 0x925, METHOD_BUFFERED, FILE_WRITE_ACCESS)