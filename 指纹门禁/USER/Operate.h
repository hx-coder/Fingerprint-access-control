
#ifndef _OPERATE_H_
#define _OPERATE_H_

#include "IIC.h"
#include "OLED.h"
#include "JIDIANQI.h"
#include "AS608.h"
#include "Key.h"

/*�ӳ�ms*/
void delayms(unsigned int ms);
/*��������*/																
void PWD_Save();
/*��ȡ����*/
void PWD_Read();

//0-9����  14ȡ��һλ 15�˳�
bit PWD_Input(uchar *pwd);

/*��ʼ������*/
void init_PWD(uchar *pwd,uchar ch);

/*����У��*/
bit PWD_Check(uchar *pwd,uchar *inPwd);

/*�޸�����*/
void PWD_Change();

/*   ���봦��     */
void dealPWD(uchar *pwd);

/*ָ�Ƶ�½*/
bit search_Finger();

/*���ָ��*/
bit add_Finger();

/*������������*/ 
bit Super_Input();

/*��������ҳ�洦��*/
void Super_deal();

//������Ӧ
void door_Select();

#endif
