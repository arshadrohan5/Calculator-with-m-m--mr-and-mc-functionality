#include "tm4c123gh6pm.h"

char scan_keypad(void)
{
	uint32_t i, cols;
	char array[5][4]={
                    {'/','0','=','c'},
                    {'7','8','9','*'},
										{'4','5','6','-'},
										{'1','2','3','+'},
										{'A','B','C','D'}
										};
	for(i=0;i<4;i++)
	{
		cols = 0x01 << i;
		GPIO_PORTE_DATA_R = cols << 3; //column0 - PE3 / column1 - PE4 //0x02
		GPIO_PORTA_DATA_R = cols << 4;//column2 - PA6 / column3 - PA7  //0x10   
		
		if((GPIO_PORTE_DATA_R & 0x04))//check PE2 - row0
		{
			while(GPIO_PORTE_DATA_R & 0x04)
				;
				return array[0][i];
		}
		if((GPIO_PORTA_DATA_R & 0x04))//check PA2 - row1
		{
			while(GPIO_PORTA_DATA_R & 0x04)
				;
				return array[1][i];
		}
		if((GPIO_PORTA_DATA_R & 0x08))//check PA3 - row2
		{
			while(GPIO_PORTA_DATA_R & 0x08)
				;
				return array[2][i];
		}
		if((GPIO_PORTA_DATA_R & 0x10))//check PA4 - row3
		{
			while(GPIO_PORTA_DATA_R & 0x10)
				;
				return array[3][i];
		}
		if((GPIO_PORTA_DATA_R & 0x20))//check PA5 - row4
		{
			while(GPIO_PORTA_DATA_R & 0x20)
				;
				return array[4][i];
		}
		
	}
	return 0;		//No key pressed
}
