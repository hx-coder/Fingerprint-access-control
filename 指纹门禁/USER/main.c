#include "Operate.h"

void main()
{
	bit sta;
	OLED_Init();
	PWD_Read();
	UART_Init();
	
	sta = Check_Dev();

	
	while(1)
	{
		door_Select();
	}
}