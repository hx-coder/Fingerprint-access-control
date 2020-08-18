
#include "OLED_IIC.h"

sbit SCL = P3^6;
sbit SDA = P3^7;

void OLED_IIC_Start()
{
	SCL = 1;
	SDA = 1;
	_nop_();
	SDA = 0;
	_nop_();
	SCL = 0;
}

void OLED_IIC_Stop()
{
	SCL = 0;
	SDA = 0;
	_nop_();
	SCL = 1;
	SDA = 1;
	_nop_();
}

void Write_IIC_Command(uchar cmd)
{
	OLED_IIC_Start();
	Write_IIC_Byte(0x78); //OLED??
	Write_IIC_Byte(0x00);
	Write_IIC_Byte(cmd); 	
	OLED_IIC_Stop();
}

void Write_IIC_Data(uchar dat)
{
	OLED_IIC_Start();
	Write_IIC_Byte(0x78); //OLED??
	Write_IIC_Byte(0x40);
	Write_IIC_Byte(dat); 	
	OLED_IIC_Stop();
}

void Write_IIC_Byte(uchar dat)
{
	uchar i;
	
	for(i = 0; i < 8; i++)
	{
		dat <<= 1;
		SDA = CY; //CY?????
		
		SCL = 1;
		_nop_();
		SCL = 0;
		_nop_();
		_nop_();
	}
	
	SDA = 1;
	SCL = 1;
	_nop_();
	SCL = 0;
	_nop_();
}