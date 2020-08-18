#include "IIC.h"

sbit SCL = P2^1;
sbit SDA = P2^0;

void IIC_delayus(unsigned int us)
{
	while(us--);
}


//??
void IIC_Start(){
	SDA = 1;
	IIC_delayus(15);
	SCL = 1;
	IIC_delayus(15);
	SDA = 0;
	IIC_delayus(15);

}
//??
void IIC_Respond(){
	unsigned char i = 0;
	SCL = 1;
	IIC_delayus(15);
	while(SDA == 1 && (i++) < 255);
	 SCL = 0;
	IIC_delayus(15);

}
//??
void IIC_Stop(){
	SDA = 0;
	IIC_delayus(15);
	SCL = 1;
	IIC_delayus(15);
	SDA = 1;
	IIC_delayus(15);

}

void IIC_SendByte(unsigned char dat){
	unsigned char i;
	for( i = 0; i < 8; i++){
			dat = dat << 1;
			SCL = 0;
			IIC_delayus(15);
			SDA = CY;//CY????
			IIC_delayus(15);
			SCL = 1;
			IIC_delayus(15);
	}
	
	SCL = 0;//????????????
	IIC_delayus(15);
	SCL = 1;
	IIC_delayus(15);

}

unsigned char IIC_ReadByte()
{
	unsigned char i,k;
	SCL = 0;
	IIC_delayus(15);
	SDA = 1;
	IIC_delayus(15);
	IIC_delayus(15);
	for(i = 0; i < 8; i++){
		SCL = 1;
		IIC_delayus(15);
		k = (k << 1) | SDA;
		SCL =0;
		IIC_delayus(15);
	}
	return k;
}

void At24c02Write(unsigned char address,unsigned char dat){
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_Respond();
	IIC_SendByte(address);
	IIC_Respond();
	IIC_SendByte(dat);
	IIC_Respond();
	IIC_Stop();
}

unsigned char At24c02Read(unsigned char address){
	unsigned char dat;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_Respond();
	IIC_SendByte(address);
	IIC_Respond();
	IIC_Start();
	IIC_SendByte(0xa1); //???
	IIC_Respond();
	dat = IIC_ReadByte();
	IIC_Respond();
	IIC_Stop();
	return dat;

}

