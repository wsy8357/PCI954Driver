// KGL3U24Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Windows.h>
#include <iostream>
#include <Public.h>

HANDLE hDevice = NULL;

bool OpenDevice();
bool CloseDevice();

int main()
{
    std::cout << "Hello World!\n";

    if (!OpenDevice())
    {
        printf("3U24设备打开失败!\r\n");
    }
    else
    {
        printf("3U24设备打开成功!\r\n");
    }

    Sleep(3000);

    if (!CloseDevice())
    {
        printf("设备关闭失败\r\n");
    }
    else
    {
        printf("设备关闭成功\r\n");
    }

    system("Pause");
    exit(1);
}

bool OpenDevice()
{
    hDevice = CreateFile(USER_DEVICE_NAME, GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (NULL == hDevice)
    {
        return FALSE;
    }

    return TRUE;
}

bool CloseDevice()
{
    if (DeleteFile(USER_DEVICE_NAME))
    {
        hDevice = NULL;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
