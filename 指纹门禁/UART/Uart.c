
#include "UART.h"

/*串口初始化*/
void UART_Init()
{
	SCON = 0x50;
	
	TMOD |= 0x20;
	TH1 = 0xfd; //9600
	TL1 = 0xfd;
	
	TR1 = 1;
	EA = 1;
}

/*发送一个字节*/
void UART_SendByte(uchar ch)
{
	SBUF = ch;
	while(!TI);
	TI = 0;
}

/*接收一个字节*/
uchar UART_GetByte()
{
	uchar ch;
	
	while(!RI);
	RI = 0;
	ch = SBUF;
	
	return ch;
}
