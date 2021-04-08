#pragma once
#include "pch.h"


typedef struct {
    uint8_t data1;
    uint8_t data2;
}SWITCH_WRITE_DATA;

//打开3U24开关量设备
HANDLE kgl3u24_open();
//根据句柄关闭3U24开关量设备
BOOL kgl3u24_close(HANDLE deviceHandle);
//控制开关量板输出
//deviceHandle 为 设备有效句柄
//param 为输入的的16的通道输出状态（1表示接通，0表示断开）
BOOL kgl3u24_output_set(HANDLE deviceHandle, UINT16 param);