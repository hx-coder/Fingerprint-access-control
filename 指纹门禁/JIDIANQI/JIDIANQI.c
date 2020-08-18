


#include "JIDIANQI.h"

sbit ds = P3^2;

/*延迟ms*/
void JI_Delayms(uint ms)
{
	uint i,j;
	
	for(i = ms; i > 0; i--)
	{
		for(j = 110; j > 0; j--);
	}
}

/*开和关,间隔10s*/
void JI_Open()
{
	ds = 0;
	
	JI_Delayms(5000);
	
	ds = 1;
}