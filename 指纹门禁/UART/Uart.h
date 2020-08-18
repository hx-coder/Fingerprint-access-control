
#ifndef _UART_H_

#define _UART_H_

#include "reg52.h"

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif

/*���ڳ�ʼ��*/
void UART_Init();

/*����һ���ֽ�*/
void UART_SendByte(uchar ch);

/*����һ���ֽ�*/
uchar UART_GetByte();


#endif