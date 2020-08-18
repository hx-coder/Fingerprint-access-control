#include "Key.h"

#define GPIO P1

unsigned int changeValue(unsigned int keyValue)
{
	if(keyValue < 3)
	{
		keyValue += 1;
	}
	else if(keyValue == 3)
	{
		keyValue = 10;
	}
	else if(keyValue == 7)
	{
		keyValue = 11;
	}
	else if( 7 < keyValue && keyValue < 11)
	{
		keyValue -= 1;
	}
	else if (keyValue == 11)
	{
		keyValue = 12;
	}
	else if(keyValue == 12)
	{
		keyValue = 14;
	}
	else if(keyValue == 13)
	{
		keyValue = 0;
	}
	else if(keyValue == 14)
	{
		keyValue = 15;
	}
	else if(keyValue == 15)
	{
		keyValue = 13;
	}
	
	return keyValue;
}

unsigned int KeyScan()
{
	unsigned int i,keyValue = 16;
	GPIO = 0x0f;
	
	if(GPIO != 0x0f)
	{
		i = 1000;
		while(i--);
		GPIO = 0x0f;
		if(GPIO != 0x0f)
		{
				switch(GPIO)
				{
					case 0x07:
						keyValue = 0;break;
					case 0x0b:
						keyValue = 1;break;
					case 0x0d:
						keyValue = 2;break;
					case 0x0e:
						keyValue = 3;break;
				}
			
			GPIO = 0xf0;
			switch(GPIO)
			{
					case 0x70:
						keyValue += 0;break;
					case 0xb0:
						keyValue += 4;break;
					case 0xd0:
						keyValue += 8;break;
					case 0xe0:
						keyValue += 12;break;
			}
			
			i = 100;
			while(GPIO != 0xf0 && i > 0)
			{
				i--;
			}
		}
		
	}
	if(keyValue != 16)
	{
		keyValue = changeValue(keyValue);
	}
	return keyValue;
}

