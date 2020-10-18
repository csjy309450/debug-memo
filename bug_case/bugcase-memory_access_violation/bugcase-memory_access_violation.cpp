// bugcase-memory_access_violation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

void bugcase_stack_arr_access_violation() 
{
    char buf[5] = { 0xf, 0xf, 0xf, 0xf, 0xf };
    buf[4] = 0;
    buf[5] = 0;
}

void bugcase_stack_pointer_access_violation_0()
{
    char buf[5] = { 0xf, 0xf, 0xf, 0xf, 0xf };
    *(buf + 4) = 0;
    *(buf + 5) = 0;
}

void bugcase_stack_pointer_access_violation_1()
{
    char buf[5] = { 0xf, 0xf, 0xf, 0xf, 0xf };
    //*(buf + 17) = 0;
    for (int i = 0; i < 17; ++i) 
    {
        if (i == 16)
        {
            *(buf + i) = 0x00;
        }
    }
}

void bugcase_heap_arr_access_violation_0()
{
    int * pbuf = new int[5];
    pbuf[4] = 0xf;
    *(pbuf + 4) = 0xe;
    pbuf[5] = 0xe;
    delete pbuf;
}

void bugcase_heap_arr_access_violation_1_release()
{
    char * pbuf = new char[2];
    memset(pbuf, 0, 2);
    *(pbuf + 2 + 8) = 0xf;
    *(pbuf - 9) = 0xf;
    delete pbuf;

    char* pbuf3 = new char[3];
    memset(pbuf3, 0, 3);
    *(pbuf3 - 8) = 0xf;
    delete pbuf3;

    char* pbuf2 = new char[5];
    memset(pbuf2, 0, 5);
    *(pbuf2 + 5 + 7) = 0xf;
    delete pbuf2;
}

void bugcase_heap_arr_access_violation_1_debug()
{
    char * pbuf = new char[2];
    memset(pbuf, 0, 2);
    *(pbuf + 2 + 12) = 0xf;//越界访问了有效内存往后12字节之后的内存
    *(pbuf - 17) = 0xf;//越界访问了有效内存往前16字节之前的内存
    delete pbuf;

    char* pbuf3 = new char[3];
    memset(pbuf3, 0, 3);
    *(pbuf3 - 16) = 0xf;//越界访问了有效内存往前16字节之内的内存
    delete pbuf3;

    char* pbuf2 = new char[5];
    memset(pbuf2, 0, 5);
    *(pbuf2 + 5 + 11) = 0xf;//越界访问了有效内存往后12字节之前的内存
    delete pbuf2;
}

int _tmain(int argc, _TCHAR* argv[])
{
    //bugcase_stack_arr_access_violation();
    //bugcase_stack_pointer_access_violation_0();
    //bugcase_stack_pointer_access_violation_1();
    //bugcase_heap_arr_access_violation_0();
    bugcase_heap_arr_access_violation_1_release();
	return 0;
}

