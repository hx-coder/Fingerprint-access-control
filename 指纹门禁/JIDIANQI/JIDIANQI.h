
#ifndef _JIDIANQI_H_

#define _JIDIANQI_H_

#include "reg52.h"

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif

/*�ӳ�ms*/
void JI_Delayms(uint ms);

/*���͹�,���10s*/
void JI_Open();

#endif