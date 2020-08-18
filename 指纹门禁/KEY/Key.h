#ifndef _KEYSCAN_H_

#define _KEYSCAN_H_

#include<reg52.h>

/*获取键值*/
unsigned int KeyScan();

/*改变键值*/
unsigned int changeValue(unsigned int keyValue);

#endif