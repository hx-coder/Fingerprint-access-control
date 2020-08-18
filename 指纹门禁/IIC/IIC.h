#ifndef _IIC_H_

#define _IIC_H_

#include<reg52.h>

void IIC_delayus(unsigned int us);

void IIC_start();

void IIC_stop();

void IIC_SendByte(unsigned char dat);

unsigned char IIC_ReadByte();

void At24c02Write(unsigned char addr,unsigned char dat);

unsigned char At24c02Read(unsigned char addr);

#endif