
#include "UART.h"

/*���ڳ�ʼ��*/
void UART_Init()
{
	SCON = 0x50;
	
	TMOD |= 0x20;
	TH1 = 0xfd; //9600
	TL1 = 0xfd;
	
	TR1 = 1;
	EA = 1;
}

/*����һ���ֽ�*/
void UART_SendByte(uchar ch)
{
	SBUF = ch;
	while(!TI);
	TI = 0;
}

/*����һ���ֽ�*/
uchar UART_GetByte()
{
	uchar ch;
	
	while(!RI);
	RI = 0;
	ch = SBUF;
	
	return ch;
}
