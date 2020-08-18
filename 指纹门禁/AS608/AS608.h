
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

/*�ӳ�ms*/
void AS_delayms(uint ms);

/*��ͷ*/
void AS_Send_Head();

/*�豸��֤*/
void AS_Send_PWD();

/*���շ�������*/
void AS_Receive(uint len);

/*��ȡͼ��*/
void AS_GetImage();

/*��ͼ�����������ŵ�BUFFER1*/
void AS_GenChar_Buff1();

/*��ͼ�����������ŵ�BUFFER2*/
void AS_GenChar_Buff2();

/*�ϲ���������*/
void AS_RegModel();

/*����ָ��*/
void AS_Search();

/*��ȡָ��ģ������*/
uint AS_GetNum();

/*ɾ��һ��ָ��*/
void AS_Delete(uint Store_Id);

/*���ָ�ƿ�*/
void AS_Empty();

/*����ָ��*/
void AS_StoreChar(uint Store_Id);

/*����豸*/
bit Check_Dev();

/*����ָ��*/
bit AS_addFinger();

/*����ָ��*/
bit AS_searchFinger(); 

/*ɾ��ָ��*/
bit del_Finger();

#endif