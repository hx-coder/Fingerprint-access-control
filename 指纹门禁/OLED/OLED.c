
#include "OLED.h"
#include "Font.h"

//延迟
void OLED_delay(uint ms)
{
	uint i;
	while(ms--)
	{
		for(i = 110; i > 0; i--);
	}

}

//初始化
void OLED_Init()
{
	OLED_delay(500);
	Write_IIC_Command(0xae);//--turn off oled panel
	Write_IIC_Command(0x00);//---set low column address
	Write_IIC_Command(0x10);//---set high column address
	Write_IIC_Command(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	Write_IIC_Command(0x81);//--set contrast control register
	Write_IIC_Command(0xcf); // Set SEG Output Current Brightness
	Write_IIC_Command(0xa1);//--Set SEG/Column Mapping     0xa0???? 0xa1??
	Write_IIC_Command(0xc8);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	Write_IIC_Command(0xa6);//--set normal display
	Write_IIC_Command(0xa8);//--set multiplex ratio(1 to 64)
	Write_IIC_Command(0x3f);//--1/64 duty
	Write_IIC_Command(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	Write_IIC_Command(0x00);//-not offset
	Write_IIC_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	Write_IIC_Command(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	Write_IIC_Command(0xd9);//--set pre-charge period
	Write_IIC_Command(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	Write_IIC_Command(0xda);//--set com pins hardware configuration
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb);//--set vcomh
	Write_IIC_Command(0x40);//Set VCOM Deselect Level
	Write_IIC_Command(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	Write_IIC_Command(0x02);//
	Write_IIC_Command(0x8d);//--set Charge Pump enable/disable
	Write_IIC_Command(0x14);//--set(0x10) disable
	Write_IIC_Command(0xa4);// Disable Entire Display On (0xa4/0xa5)
	Write_IIC_Command(0xa6);// Disable Inverse Display On (0xa6/a7) 
	Write_IIC_Command(0xaf);//--turn on oled panel   

	OLED_Fill(0x00);  //清屏
	OLED_SetPos(0,0); 	
}

//设置光标
void OLED_SetPos(uchar x, uchar y)
{
	//行显示
	Write_IIC_Command(0xb0+y);
	Write_IIC_Command(((x&0xf0) >> 4) | 0x10);//高位
	Write_IIC_Command((x&0x0f) | 0x01);  //低位
}

//清屏
void OLED_Fill(uchar bmp_dat)
{
	unsigned char y,x;
	for(y = 0; y < 8; y++)
	{
			Write_IIC_Command(0xb0+y);
			Write_IIC_Command(0x01);
			Write_IIC_Command(0x10);
			for(x = 0; x < 128; x++)
				Write_IIC_Data(bmp_dat);
	}
}

//请输入6位密码
void OLED_ShowWordMessage()
{
	uint i,j;
	OLED_Fill(0);  //清屏
	for(i = 0; i < 7; i++)
	{
		OLED_SetPos(18 * i, 2);
		
		for(j = 0; j < 16; j++)
		{//前16位
			Write_IIC_Data(wordMessage[2 * i][j]);
		}
		
		OLED_SetPos(18 * i, 3);
		//后16位
		for(j = 0; j < 16; j++)
		{
			Write_IIC_Data(wordMessage[2 * i + 1][j]);
		}
	}
}

//旧Or新 密码
void OLED_ShowNewOrOld(unsigned int num)
{
	uint i,j;
	
	OLED_Fill(0);
	
	OLED_SetPos(35, 2);
	
	//显示新或者旧
	for(j = 0; j < 16; j++)
	{//前16位
		Write_IIC_Data(newAndold[num][j]);
	}
	OLED_SetPos(35, 3);
	//后16位
	for(j = 0; j < 16; j++)
	{
		Write_IIC_Data(newAndold[num][j]);
	}
	//密码
	for(i = 0; i < 2; i++)
	{
		OLED_SetPos(35 * (i + 2), 2);
		
		for(j = 0; j < 16; j++)
		{//前16位
			Write_IIC_Data(errorMessage[2 * i][j]);
		}
		
		OLED_SetPos(35 * (i + 2), 3);
		//后16位
		for(j = 0; j < 16; j++)
		{
			Write_IIC_Data(errorMessage[2 * i + 1][j]);
		}
	}
}

//密码错误
void OLED_ShowErrorMessage()
{
	uint i,j;
	OLED_Fill(0); //清屏

	for(i = 0; i < 4; i++)
	{
		OLED_SetPos(25 * (i + 1), 2);
		
		for(j = 0; j < 16; j++)
		{//前16位
			Write_IIC_Data(errorMessage[2 * i][j]);
		}
		
		OLED_SetPos(25 * (i + 1), 3);
		//后16位
		for(j = 0; j < 16; j++)
		{
			Write_IIC_Data(errorMessage[2 * i + 1][j]);
		}
	}
}

//欢迎大哥
void OLED_ShowWel()
{
	uint i,j;
	OLED_Fill(0);  //清屏
	for(i = 0; i < 4; i++)  //第几个字
	{
		OLED_SetPos(25 * (i + 1), 2);
		
		for(j = 0; j < 16; j++)
		{//前16位
			Write_IIC_Data(entryMessage[2 * i][j]);
		}
		
		OLED_SetPos(25 * (i + 1), 3);
		//后16位
		for(j = 0; j < 16; j++)
		{
			Write_IIC_Data(entryMessage[2 * i + 1][j]);
		}
	}
}

//显示数字
void OLED_ShowNum(uint no,uchar num)
{
	uint j;
	
	OLED_SetPos(18 * no, 4);
	for(j = 0; j < 16; j++)
	{//前16位
		Write_IIC_Data(Number[num][j]);
	}
		
	OLED_SetPos(18 * no, 5);
	//后16位
	for(j = 0; j < 16; j++)
	{
		Write_IIC_Data(Number[num][j]);
	}
}

//显示*
void OLED_ShowHidenWord(uint no)
{
	uint j;
	
	OLED_SetPos(18 * no, 4);
	for(j = 0; j < 16; j++)
	{//前16位
		Write_IIC_Data(maskMessage[0][j]);
	}
		
	OLED_SetPos(18 * no, 5);
	//后16位
	for(j = 0; j < 16; j++)
	{
		Write_IIC_Data(maskMessage[1][j]);
	}
}
	
//清除*
void OLED_clearHidenWord(uint no)
{
	unsigned char i,j;
	
	for(i = 4; i < 6; i++)
	{
		OLED_SetPos(18 * no, i);
		
		for(j = 18 * no; j < 18 * no + 16; j++)
		{
				Write_IIC_Data(0);
		}
	}
}

//请按下手指
void OLED_ShowMiko()
{
	uint i,j;
	OLED_Fill(0x00);
	for( i = 0; i < 5; i++)  //第几个字
	{
		OLED_SetPos(18 * i, 2);
		
		for(j = 0; j < 16; j++)
		{//前16位
			Write_IIC_Data(mikorMessage[2 * i][j]);
		}
		
		OLED_SetPos(18 * i, 3);
		//后16位
		for(j = 0; j < 16; j++)
		{
			Write_IIC_Data(mikorMessage[2 * i + 1][j]);
		}
	}
}	

//修改成功
void OLED_ShowChange()
{
	uint i,j;
	OLED_Fill(0);  //清屏
	for(i = 0; i < 4; i++)
	{
		OLED_SetPos(25 * (i + 1), 2);
		
		for(j = 0; j < 16; j++)
		{//前16位
			Write_IIC_Data(ChangeMessage[2 * i][j]);
		}
		
		OLED_SetPos(25 * (i + 1), 3);
		//后16位
		for(j = 0; j < 16; j++)
		{
			Write_IIC_Data(ChangeMessage[2 * i + 1][j]);
		}
	}
}
//录入成功
void OLED_ShowMikoOk()
{
	uint i,j;
	OLED_Fill(0);  //清屏
	for(i = 1; i < 5; i++)
	{
		OLED_SetPos(25 * (i + 1), 2);
		
		for(j = 0; j < 16; j++)
		{//前16位
			Write_IIC_Data(OkMessage[2 * i][j]);
		}
		
		OLED_SetPos(25 * (i + 1), 3);
		//后16位
		for(j = 0; j < 16; j++)
		{
			Write_IIC_Data(OkMessage[2 * i + 1][j]);
		}
	}
}
	
//超级密码
void OLED_ShowSuper()
{
	uint i,j;
	OLED_Fill(0);  //清屏
	for(i = 0; i < 4; i++)
	{
		OLED_SetPos(25 * (i + 1), 2);
		
		for(j = 0; j < 16; j++)
		{//前16位
			Write_IIC_Data(super[2 * i][j]);
		}
		
		OLED_SetPos(25 * (i + 1), 3);
		//后16位
		for(j = 0; j < 16; j++)
		{
			Write_IIC_Data(super[2 * i + 1][j]);
		}
	}
}


//void OLED_ShowMikoExit();
//普通选择界面
void OLED_Showfirst()
{
	unsigned char i,j;
	
	for(i = 0; i < 8; i++)
	{
		OLED_SetPos(0, i);
		
		for(j = 0; j < 128; j++)
		{
				Write_IIC_Data(Firstword[i * 128 + j]);
		}
	}
}

//超级选择界面
void OLED_ShowSuperF()
{
	unsigned char i,j;
	
	for(i = 0; i < 8; i++)
	{
		OLED_SetPos(0, i);
		
		for(j = 0; j < 128; j++)
		{
				Write_IIC_Data(superShow[i * 128 + j]);
		}
	}
}
