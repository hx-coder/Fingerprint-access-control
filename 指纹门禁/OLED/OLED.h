
#ifndef _OLED_H_
#define _OLED_H_

#include "OLED_IIC.h"
#include "font.h"

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif

//�ӳ�
void OLED_delay(uint ms);

//��ʼ��
void OLED_Init();

//���ù��
void OLED_SetPos(uchar x, uchar y);

//����
void OLED_Fill(uchar bmp_dat);

//������6λ����
void OLED_ShowWordMessage();

//��Or�� ����
void OLED_ShowNewOrOld(unsigned int num);

//�������
void OLED_ShowErrorMessage();

//��ӭ���
void OLED_ShowWel();

//��ʾ����
void OLED_ShowNum(uint no,uchar num);
//��ʾ*
void OLED_ShowHidenWord(uint no);
//���*
void OLED_clearHidenWord(uint no);
//�밴����ָ
void OLED_ShowMiko();
//�޸ĳɹ�
void OLED_ShowChange();
//¼��ɹ�
void OLED_ShowMikoOk();
//��������
void OLED_ShowSuper();


//void OLED_ShowMikoExit();
//��ͨѡ�����
void OLED_Showfirst();
//����ѡ�����
void OLED_ShowSuperF();

#endif