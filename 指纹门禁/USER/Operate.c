
#include "Operate.h"


unsigned char PWD[] = {1,2,3,4,5,6},PWD_Sta = 1;
unsigned char inputPWD[6] = {0},tempPWD[6] = {'-','-','-','-','-','-'};
unsigned char superPWD[6] = {6,5,4,3,2,1};

sbit LED = P2^3; 

/*�ӳ�ms*/
void delayms(unsigned int ms)
{
	unsigned int i,j;
	for(i = ms; i > 0; i--)
	{
		for(j = 110; j > 0; j--);
	}
}	


/*��������*/																
void PWD_Save()
{

	At24c02Write(1,PWD[0]);
	delayms(1);
	At24c02Write(2,PWD[1]);
	delayms(1);
	At24c02Write(3,PWD[2]);
	delayms(1);
	At24c02Write(4,PWD[3]);
	delayms(1);
	At24c02Write(5,PWD[4]);
	delayms(1);
	At24c02Write(6,PWD[5]);
	delayms(1);
}

/*��ȡ����*/
void PWD_Read()
{
	unsigned char first_load = 0;
	first_load = At24c02Read(0);
	
	if(first_load == 1)
	{
		PWD[0] = At24c02Read(1);
		PWD[1] = At24c02Read(2);
		PWD[2] = At24c02Read(3);
		PWD[3] = At24c02Read(4);
		PWD[4] = At24c02Read(5);
		PWD[5] = At24c02Read(6);
		
	}
	else
	{
		At24c02Write(0,1);
		delayms(1);
		PWD_Save();
	}
}

/*��������*/
//0-9����  14ȡ��һλ 15�˳�
bit PWD_Input(uchar *pwd)
{
	unsigned int keyValue = 16, i = 0;

	for(i = 0; i < 6; i++,pwd++)
	{
		while((keyValue > 9 && keyValue < 14) || keyValue == 16)
		{
			keyValue = KeyScan();
		}
		
		if(keyValue == 14)  // * ȡ��һλ
		{
			if(i == 0)
			{
				return 0;
			}
			OLED_clearHidenWord(i - 1);   //����*��
			pwd -= 2;
			i -= 2;
		}
		else if(keyValue == 15)   //ȡ��
		{
			return 0;
		}
		else
		{
			OLED_ShowNum(i,keyValue);	
			delayms(100);
			OLED_ShowHidenWord(i);
			
			*pwd = keyValue;
			}
			keyValue = 16;
	}
	return 1;
}

/*��ʼ������*/
void init_PWD(uchar *pwd,uchar ch)
{
	unsigned char i;
	
	for(i = 0; i < 6; i++,pwd++)
	{
		*pwd = ch;
	}
}

/*����У��*/
bit PWD_Check(uchar *pwd,uchar *inPwd)
{
	unsigned char i;
	bit confirm = 1;
	
	for(i = 0; i < 6; i++,pwd++,inPwd++)
	{
		if(*pwd != *inPwd)
		{
			confirm = 0;
		}
	}
	
	return confirm;
}

/*�޸�����*/
void PWD_Change()
{
	unsigned int i = 0;
	bit sta = 0;
	
	OLED_ShowNewOrOld(1);
	sta = PWD_Input(inputPWD);	
	//�Ƿ��˳�
	if(sta == 0)
	{
		return;
	}
	
	sta = PWD_Check(PWD,inputPWD);  //У��
	init_PWD(inputPWD,'0');   //��0
	if(sta == 0)  //ԭ�����������
	{
		OLED_ShowErrorMessage();
		return;
	}
	
	OLED_ShowNewOrOld(0);
	sta = PWD_Input(inputPWD);	
	//�Ƿ��˳�
	if(sta == 0)
	{
		init_PWD(inputPWD,'0'); //��0
		return;
	}
	
	for(i = 0; i < 6; i++)
	{
		PWD[i] = inputPWD[i];
	}
	PWD_Save();
	init_PWD(inputPWD,'0'); //��0
	OLED_ShowChange();  //��ʾ��Ϣ
}


/*   ���봦��     */
void dealPWD(uchar *pwd)
{
	bit sta = 0;
	uint keyValue = 16;
	bit pwd_check = 0;
	
	sta = PWD_Input(inputPWD);   //��������
	if(sta == 0)
	{
		init_PWD(inputPWD,'0');
		return;
	}	
	
	pwd_check = PWD_Check(pwd,inputPWD); //У��
	if(pwd_check == 1)
	{
			OLED_ShowWel();
			LED = 0;
			JI_Open();
	}
	else
	{
		OLED_ShowErrorMessage();
	}	
	init_PWD(inputPWD,'0');  //��ʼ����������
}


/*ָ�Ƶ�½*/
bit search_Finger()
{
	bit sta = 0;
	uint i = 0;
	do{
		sta = AS_searchFinger();
		i++;
	}while(sta == 0 && i < 10);
	
	if(sta == 1)
	{
		OLED_ShowWel();
		LED = 0;
		JI_Open();
	}
	
	return sta;
}

/*���ָ��*/
bit add_Finger()
{
	bit sta = 0;
	uint i = 0;
	do{
		i++;
		sta = AS_addFinger();
		
	}while(sta == 0 && i < 10);
	
	if(sta == 1)
	{
		OLED_ShowMikoOk();
	}
	
	return sta;
}


/*������������*/ 
bit Super_Input()
{
	bit sta = 0;
	
	sta = PWD_Input(inputPWD);
	
	if(sta == 1)
	{
		sta = PWD_Check(superPWD,inputPWD);
	}
	init_PWD(inputPWD,'0');
	
	return sta;
}

/*��������ҳ�洦��*/
void Super_deal()
{
	unsigned int keyValue = 16;
	bit sta = 0;
	
	do{
		OLED_ShowSuperF();
		keyValue = KeyScan();
		sta = 0;
		
		if(keyValue == 1)     //���ָ��
		{
				sta = add_Finger();
		}
		else if(keyValue ==  2)   //ɾ��ָ��
		{
//			while(sta == 0)
//			{
//		//		sta = del_Finger();
//			}
			AS_Empty();
		}
		else if(keyValue == 3)    //�޸�����
		{
			PWD_Change();
		}
	}while(keyValue != 15);     // # �˳�

}

//������Ӧ
void door_Select()
{
	bit sta = 0;
	unsigned int keyValue = 16;
	
	LED = 1;
	OLED_Showfirst();
	keyValue = KeyScan();
	if(keyValue == 10)   // A ��������
	{
			OLED_ShowWordMessage();
			dealPWD(PWD);		
	}
	else if(keyValue == 12)   // C ָ������
	{
		sta = search_Finger();
	}
	else if(keyValue == 13)    // D ���볬������Ա
	{
		OLED_ShowSuper();
			
		sta = Super_Input();
		if(sta == 1)
		{
				LED = 0;
				Super_deal();
		}
		else
		{
				OLED_ShowErrorMessage();
		}
	}
}
