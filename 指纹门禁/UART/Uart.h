
#ifndef _UART_H_

#define _UART_H_

#include "reg52.h"

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif

/*串口初始化*/
void UART_Init();

/*发送一个字节*/
void UART_SendByte(uchar ch);

/*接收一个字节*/
uchar UART_GetByte();


#endif