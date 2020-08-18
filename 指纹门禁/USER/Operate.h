
#ifndef _OPERATE_H_
#define _OPERATE_H_

#include "IIC.h"
#include "OLED.h"
#include "JIDIANQI.h"
#include "AS608.h"
#include "Key.h"

/*延迟ms*/
void delayms(unsigned int ms);
/*保存密码*/																
void PWD_Save();
/*读取密码*/
void PWD_Read();

//0-9输入  14取消一位 15退出
bit PWD_Input(uchar *pwd);

/*初始化密码*/
void init_PWD(uchar *pwd,uchar ch);

/*密码校验*/
bit PWD_Check(uchar *pwd,uchar *inPwd);

/*修改密码*/
void PWD_Change();

/*   密码处理     */
void dealPWD(uchar *pwd);

/*指纹登陆*/
bit search_Finger();

/*添加指纹*/
bit add_Finger();

/*超级管理输入*/ 
bit Super_Input();

/*超级管理页面处理*/
void Super_deal();

//按键响应
void door_Select();

#endif
