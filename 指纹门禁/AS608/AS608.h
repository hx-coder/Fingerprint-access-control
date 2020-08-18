
#ifndef _AS608_H_

#define _AS608_H_

#include "reg52.h"
#include "UART.h"
#include "OLED.h"

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif

/*延迟ms*/
void AS_delayms(uint ms);

/*包头*/
void AS_Send_Head();

/*设备验证*/
void AS_Send_PWD();

/*接收返回数据*/
void AS_Receive(uint len);

/*获取图形*/
void AS_GetImage();

/*将图像生成特征放到BUFFER1*/
void AS_GenChar_Buff1();

/*将图像生成特征放到BUFFER2*/
void AS_GenChar_Buff2();

/*合并生成特征*/
void AS_RegModel();

/*搜索指纹*/
void AS_Search();

/*获取指纹模板数量*/
uint AS_GetNum();

/*删除一个指纹*/
void AS_Delete(uint Store_Id);

/*清空指纹库*/
void AS_Empty();

/*保持指纹*/
void AS_StoreChar(uint Store_Id);

/*检查设备*/
bit Check_Dev();

/*增加指纹*/
bit AS_addFinger();

/*搜索指纹*/
bit AS_searchFinger(); 

/*删除指纹*/
bit del_Finger();

#endif