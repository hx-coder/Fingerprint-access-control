
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

//延迟
void OLED_delay(uint ms);

//初始化
void OLED_Init();

//设置光标
void OLED_SetPos(uchar x, uchar y);

//清屏
void OLED_Fill(uchar bmp_dat);

//请输入6位密码
void OLED_ShowWordMessage();

//旧Or新 密码
void OLED_ShowNewOrOld(unsigned int num);

//密码错误
void OLED_ShowErrorMessage();

//欢迎大哥
void OLED_ShowWel();

//显示数字
void OLED_ShowNum(uint no,uchar num);
//显示*
void OLED_ShowHidenWord(uint no);
//清除*
void OLED_clearHidenWord(uint no);
//请按下手指
void OLED_ShowMiko();
//修改成功
void OLED_ShowChange();
//录入成功
void OLED_ShowMikoOk();
//超级密码
void OLED_ShowSuper();


//void OLED_ShowMikoExit();
//普通选择界面
void OLED_Showfirst();
//超级选择界面
void OLED_ShowSuperF();

#endif