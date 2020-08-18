
#include "AS608.h"

volatile uchar res[32];
uint finger_id = 0;

/*相关协议*/

code uchar Get_Device[10] ={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//口令验证
code uchar Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //协议包头
code uchar Get_Img[6] = {0x01,0x00,0x03,0x01,0x00,0x05};    //获得指纹图像
code uchar Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //获得模版总数
code uchar Search[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xE7,0x00,0xF8}; //搜索指纹搜索范围0 - 999,使用BUFFER1中的特征码搜索
code uchar Search_0_9[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x13,0x00,0x21}; //搜索0-9号指纹
code uchar Img_To_Buffer1[7]={0x01,0x00,0x04,0x02,0x01,0x00,0x08}; //将图像放入到BUFFER1
code uchar Img_To_Buffer2[7]={0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //将图像放入到BUFFER2
code uchar Reg_Model[6]={0x01,0x00,0x03,0x05,0x00,0x09}; //将BUFFER1跟BUFFER2合成特征模版
code uchar Delete_All_Model[6]={0x01,0x00,0x03,0x0d,0x00,0x11};//删除指纹模块里所有的模版

volatile uchar Delete_Model[10]={0x01,0x00,0x07,0x0c,0x00,0x00,0x00,0x01,0x00,0x15};//删除指纹模块里某一个指纹
volatile uchar  Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置


void AS_delayms(uint ms)
{
	uint i,j;
	
	for(i = ms; i > 0; i--)
	{
			for(j = 110; j > 0; j--);
	}
}

/*包头*/
void AS_Send_Head()
{
	uint i;
	
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Pack_Head[i]);
	}
}

/*设备验证*/
void AS_Send_PWD()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 10; i++)
	{
		UART_SendByte(Get_Device[i]);
	}

}

/*接收返回数据*/
void AS_Receive(uint len)
{
	uint i;
	for(i= 0; i < len; i++)
	{
		res[i] = UART_GetByte();
	}
}

/*获取图形*/
void AS_GetImage()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Get_Img[i]);
	}
}

/*将图像生成特征放到BUFFER1*/
void AS_GenChar_Buff1()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 7; i++)
	{
		UART_SendByte(Img_To_Buffer1[i]);
	}
}

/*将图像生成特征放到BUFFER2*/
void AS_GenChar_Buff2()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 7; i++)
	{
		UART_SendByte(Img_To_Buffer2[i]);
	}
}

/*合并生成特征*/
void AS_RegModel()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Reg_Model[i]);
	}
}

/*搜索指纹*/
void AS_Search()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 11; i++)
	{
		UART_SendByte(Search[i]);
	}
}

/*获取指纹模板数量*/
uint AS_GetNum()
{
	uint dat;
	uint i;
	AS_Send_Head();
//	UART_SendStr(Get_Templete_Count);
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Get_Templete_Count[i]);
	}
	AS_Receive(14);
	
	dat = res[10] * 256 + res[11];
	
	return dat;
}

/*删除一个指纹*/
void AS_Delete(uint Store_Id)
{
	uchar i;
	unsigned long temp = 0;
	
	Delete_Model[4] = (Store_Id & 0xFF00) >> 8;   //高位
	Delete_Model[5] = Store_Id & 0x00FF;   //低位
	
	for(i = 0; i < 8; i++)
	{
		temp += Delete_Model[i];
	}
	
	Delete_Model[8] = (temp & 0x00FF00) >> 8;   //高位
	Delete_Model[9] = temp & 0x0000FF;   //低位
	
	AS_Send_Head();
	
	for(i= 0; i < 10; i++)
	{
		UART_SendByte(Delete_Model[i]);
	}
}

/*清空指纹库*/
void AS_Empty()
{
	uint i;
	AS_Send_Head();
	
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Delete_All_Model[i]);
	}
}

/*保存指纹*/
void AS_StoreChar(uint Store_Id)
{
	uchar i;
	uint temp = 0;
	
	Save_Finger[5] = Store_Id / 256;
	Save_Finger[6] = Store_Id % 256;
	
	for(i = 0; i < 7; i++)						//计算校验和
	{
		temp = temp + Save_Finger[i];
	}
	Save_Finger[7]=temp / 256;
	Save_Finger[8]=temp % 256;
	
	AS_Send_Head();
	
	for(i= 0; i < 9; i++)
	{
		UART_SendByte(Save_Finger[i]);
	}
}

/*检查设备*/
bit Check_Dev()
{
	bit stat = 0;
	
	AS_Send_PWD();
	AS_Receive(12);
	
	if(res[9] == 0)
	{
		stat = 1;   //检验到设备
	}
	
	return stat;
}

/*增加指纹*/
bit AS_addFinger()
{
	bit stat = 0;
	finger_id = AS_GetNum();
	
	OLED_ShowMiko();
	do{
		AS_GetImage();
		AS_Receive(12);
		
		if(res[9] == 0)  //获取到指纹
		{
			break;
		}
	}while(1);
	
	AS_delayms(100);
	AS_GenChar_Buff1();
	AS_Receive(12);
	
//	//查询是否存在指纹
//	AS_Search();
//	AS_Receive(16);
//	
//	if(res[9] == 0)
//	{
//		stat = 1;
//		
//		OLED_ShowMikoExit();
//		AS_delayms(1000);
//		
//		return 1;
//	}
	
	if(res[9] == 0)
	{
		AS_delayms(100);
		OLED_ShowMiko();
		do{
			AS_GetImage();
			AS_Receive(12);
		
			if(res[9] == 0)  //获取到指纹
			{
				break;
			}
		}while(1);
		
		AS_delayms(100);
		AS_GenChar_Buff2();
		AS_Receive(12);
		
		AS_RegModel();
		AS_Receive(12);
		
		AS_StoreChar(finger_id);
		AS_Receive(12);
		AS_delayms(100);
		
		if(res[9] == 0)
		{
			stat = 1;
		}
	}
	
	return stat;
}

/*搜索指纹*/
bit AS_searchFinger()
{
	bit stat = 0;
	
	OLED_ShowMiko();
	
	finger_id = 0;
	
	do{
		AS_GetImage();
		AS_Receive(12);
		
		if(res[9] == 0)  //获取到指纹
		{
			break;
		}
	}while(1);
	
	AS_delayms(100);
	AS_GenChar_Buff1();
	AS_Receive(12);
	
	AS_Search();
	AS_Receive(16);
	
	if(res[9] == 0)
	{
		stat = 1;
		finger_id = res[10] * 256 + res[11];
	}
	return stat;
}

/*删除指纹*/
bit del_Finger()
{
	bit sta = 0;
	uint i = 0;
	
	OLED_ShowMiko();
	do
	{
		sta = AS_searchFinger();
		i++;
	}while(sta == 0 && i < 100);
	
	sta = 0;
	AS_Delete(finger_id);
	AS_Receive(12);
	
	if(res[9] == 0)
	{
		sta = 1;
	}
	
	return sta;
}