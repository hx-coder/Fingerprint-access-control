
#ifndef _OLED_IIC_H_
#define _OLED_IIC_H_

#include "reg52.h"
#include "intrins.h"

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif

void OLED_IIC_Start();

void OLED_IIC_Stop();

void Write_IIC_Command(uchar cmd);

void Write_IIC_Data(uchar dat);

void Write_IIC_Byte(uchar dat);


#endif