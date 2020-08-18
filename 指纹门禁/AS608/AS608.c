
#include "AS608.h"

volatile uchar res[32];
uint finger_id = 0;

/*���Э��*/

code uchar Get_Device[10] ={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//������֤
code uchar Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //Э���ͷ
code uchar Get_Img[6] = {0x01,0x00,0x03,0x01,0x00,0x05};    //���ָ��ͼ��
code uchar Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //���ģ������
code uchar Search[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xE7,0x00,0xF8}; //����ָ��������Χ0 - 999,ʹ��BUFFER1�е�����������
code uchar Search_0_9[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x13,0x00,0x21}; //����0-9��ָ��
code uchar Img_To_Buffer1[7]={0x01,0x00,0x04,0x02,0x01,0x00,0x08}; //��ͼ����뵽BUFFER1
code uchar Img_To_Buffer2[7]={0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //��ͼ����뵽BUFFER2
code uchar Reg_Model[6]={0x01,0x00,0x03,0x05,0x00,0x09}; //��BUFFER1��BUFFER2�ϳ�����ģ��
code uchar Delete_All_Model[6]={0x01,0x00,0x03,0x0d,0x00,0x11};//ɾ��ָ��ģ�������е�ģ��

volatile uchar Delete_Model[10]={0x01,0x00,0x07,0x0c,0x00,0x00,0x00,0x01,0x00,0x15};//ɾ��ָ��ģ����ĳһ��ָ��
volatile uchar  Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//��BUFFER1�е��������ŵ�ָ����λ��


void AS_delayms(uint ms)
{
	uint i,j;
	
	for(i = ms; i > 0; i--)
	{
			for(j = 110; j > 0; j--);
	}
}

/*��ͷ*/
void AS_Send_Head()
{
	uint i;
	
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Pack_Head[i]);
	}
}

/*�豸��֤*/
void AS_Send_PWD()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 10; i++)
	{
		UART_SendByte(Get_Device[i]);
	}

}

/*���շ�������*/
void AS_Receive(uint len)
{
	uint i;
	for(i= 0; i < len; i++)
	{
		res[i] = UART_GetByte();
	}
}

/*��ȡͼ��*/
void AS_GetImage()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Get_Img[i]);
	}
}

/*��ͼ�����������ŵ�BUFFER1*/
void AS_GenChar_Buff1()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 7; i++)
	{
		UART_SendByte(Img_To_Buffer1[i]);
	}
}

/*��ͼ�����������ŵ�BUFFER2*/
void AS_GenChar_Buff2()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 7; i++)
	{
		UART_SendByte(Img_To_Buffer2[i]);
	}
}

/*�ϲ���������*/
void AS_RegModel()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Reg_Model[i]);
	}
}

/*����ָ��*/
void AS_Search()
{
	uint i;
	
	AS_Send_Head();
	for(i= 0; i < 11; i++)
	{
		UART_SendByte(Search[i]);
	}
}

/*��ȡָ��ģ������*/
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

/*ɾ��һ��ָ��*/
void AS_Delete(uint Store_Id)
{
	uchar i;
	unsigned long temp = 0;
	
	Delete_Model[4] = (Store_Id & 0xFF00) >> 8;   //��λ
	Delete_Model[5] = Store_Id & 0x00FF;   //��λ
	
	for(i = 0; i < 8; i++)
	{
		temp += Delete_Model[i];
	}
	
	Delete_Model[8] = (temp & 0x00FF00) >> 8;   //��λ
	Delete_Model[9] = temp & 0x0000FF;   //��λ
	
	AS_Send_Head();
	
	for(i= 0; i < 10; i++)
	{
		UART_SendByte(Delete_Model[i]);
	}
}

/*���ָ�ƿ�*/
void AS_Empty()
{
	uint i;
	AS_Send_Head();
	
	for(i= 0; i < 6; i++)
	{
		UART_SendByte(Delete_All_Model[i]);
	}
}

/*����ָ��*/
void AS_StoreChar(uint Store_Id)
{
	uchar i;
	uint temp = 0;
	
	Save_Finger[5] = Store_Id / 256;
	Save_Finger[6] = Store_Id % 256;
	
	for(i = 0; i < 7; i++)						//����У���
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

/*����豸*/
bit Check_Dev()
{
	bit stat = 0;
	
	AS_Send_PWD();
	AS_Receive(12);
	
	if(res[9] == 0)
	{
		stat = 1;   //���鵽�豸
	}
	
	return stat;
}

/*����ָ��*/
bit AS_addFinger()
{
	bit stat = 0;
	finger_id = AS_GetNum();
	
	OLED_ShowMiko();
	do{
		AS_GetImage();
		AS_Receive(12);
		
		if(res[9] == 0)  //��ȡ��ָ��
		{
			break;
		}
	}while(1);
	
	AS_delayms(100);
	AS_GenChar_Buff1();
	AS_Receive(12);
	
//	//��ѯ�Ƿ����ָ��
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
		
			if(res[9] == 0)  //��ȡ��ָ��
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

/*����ָ��*/
bit AS_searchFinger()
{
	bit stat = 0;
	
	OLED_ShowMiko();
	
	finger_id = 0;
	
	do{
		AS_GetImage();
		AS_Receive(12);
		
		if(res[9] == 0)  //��ȡ��ָ��
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

/*ɾ��ָ��*/
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