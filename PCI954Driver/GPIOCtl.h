#pragma once
EXTERN_C_START

typedef struct _COM_SET_MODE
{
	UCHAR ComNum;		//串口号
	ULONG Baud;			//波特率
	UCHAR Data;			//数据位
	UCHAR Stop;			//停止位
	UCHAR Parity;		//校验位
	UCHAR Count;		//Fifo中断级别
	UCHAR Mode;			//工作模式
}COM_SET_MODE, *PCOM_SET_MODE;

EXTERN_C_END