#include "liquidcrystal.h"
#include "keypad.h"
#include "baseN.h"
#include <string.h>
#include "Flash.h"
/*
	THIS PROGRAM USES LCD IN 4 BIT MODE
	PF1 - RS
	PF2 - R/W
	PF3 - EN
	
	PB4 - D4
	PB5 - D5
	PB6 - D6
	PB7 - D7
	
	AND USES 5X4 KEYPAD
	PE2 - ROW0
	PA2 - ROW1
	PA3 - ROW2
	PA4 - ROW3
	PA5 - ROW4
	PA6 - COL2
	PA7 - COL3
	PE3 - COL0
	PE4 - COL1
*/
void ports_init(void);
char scan_keypad(void);
uint32_t array2num(uint8_t *arr, int index);
void baseN(void);
int main()
{
	char key_pressed_current;
	uint8_t num_array[8];
	int index;
	char op;
	int op_flag;
	int op2_flag;
	int op1_flag;
	int flash_data_stored;
	int flash_data_current;
	int flash_reset_val;
	int operand1;
	int operand2;
	int result;
	int div; 
	key_pressed_current = 0;
	op_flag=0;
	op2_flag=0;
	op1_flag=0;
	op=0;
	index=0;
	flash_data_current=0;
	flash_data_stored=0;
	flash_reset_val = 0;
	operand1=0;
	operand2=0;
	result=0;
	ports_init();
	Flash_Enable();
	init_lcd();
	lcd_clear();
	lcd_goto_pos (1, 1);
	lcd_send_string("1.Basic 2.Base-N");
	lcd_goto_pos(2,1);
	do
		{
			delay(100);
			key_pressed_current=scan_keypad();
		}while(key_pressed_current==0);
	switch(key_pressed_current)
	{
		case '2':
		  baseN();
			break;
		case '1':
			lcd_clear();
		  lcd_goto_pos(1,1);
			while(1)
			{
				//checks which key is pressed
				do
				{
					if(key_pressed_current=='A'||key_pressed_current=='B')
						break;
					
					delay(100);
					key_pressed_current=scan_keypad();
				}while(key_pressed_current==0);
				if(key_pressed_current == 'c')
				{
					lcd_clear();
					lcd_goto_pos (1, 1);
					key_pressed_current = 0;
					operand1=0;
					operand2=0;
				}
				//Displays the pressed key on LCD
				if(key_pressed_current != 0)
				{
							
							switch(key_pressed_current)
							{
								case '0':
									lcd_send_data(key_pressed_current);
									num_array[index++]=0;
									break;
								case '1':
									lcd_send_data(key_pressed_current);
									num_array[index++]=1;
									break;
								case '2':
									lcd_send_data(key_pressed_current);
									num_array[index++]=2;
									break;
								case '3':
									lcd_send_data(key_pressed_current);
									num_array[index++]=3;
									break;
								case '4':
									lcd_send_data(key_pressed_current);
									num_array[index++]=4;
									break;
								case '5':
									lcd_send_data(key_pressed_current);
									num_array[index++]=5;
									break;
								case '6':
									lcd_send_data(key_pressed_current);
									num_array[index++]=6;
									break;
								case '7':
									lcd_send_data(key_pressed_current);
									num_array[index++]=7;
									break;
								case '8':
									lcd_send_data(key_pressed_current);
									num_array[index++]=8;
									break;
								case '9':
									lcd_send_data(key_pressed_current);
									num_array[index++]=9;
									break;
								case 'A':
									if(flash_data_current==0)
										flash_data_current=array2num(num_array,index-1);
									
									Flash_Read(&flash_data_stored,1);
								  flash_data_current = flash_data_stored+flash_data_current;
								  Flash_Write(&flash_data_current,1);
									key_pressed_current=0;
									break;
								case 'B':
									if(flash_data_current==0)
										flash_data_current=array2num(num_array,index-1);
									
									Flash_Read(&flash_data_stored,1);
								  flash_data_current = flash_data_stored - flash_data_current;
								  Flash_Write(&flash_data_current,1);
									key_pressed_current=0;
									break;
								case 'C':
									Flash_Read(&flash_data_stored,1);
									if(op1_flag==0)
									{
										operand1 = flash_data_stored;
										op1_flag=1;
									}
									if(op_flag==1 && op2_flag==0)
									{
										operand2 = flash_data_stored;
										op2_flag=1;
									}
								  if(flash_data_stored < 0){
										lcd_send_data('-');
										flash_data_stored = flash_data_stored * (-1);
									}
									display_num((uint32_t)flash_data_stored);
									key_pressed_current=0;
									break;
								case 'D':
									Flash_Write(&flash_reset_val,1);
								  key_pressed_current=0;
									break;
								case '+':
									lcd_send_data(key_pressed_current);
									op='+';
									op_flag++;
									if(op1_flag==0){
										operand1=array2num(num_array,index-1);
										op1_flag=1;;
									}
									index=0;
									break;
								case '-':
									lcd_send_data(key_pressed_current);
									op='-';
									op_flag++;
									if(op1_flag==0){
										operand1=array2num(num_array,index-1);
										op1_flag=1;;
									}
									index=0;
									break;
								case '*':
									lcd_send_data(key_pressed_current);
									op='*';
									op_flag++;
									if(op1_flag==0){
										operand1=array2num(num_array,index-1);
										op1_flag=1;;
									}
									index=0;
									break;
								case '/':
									lcd_send_data(key_pressed_current);
									op='/';
									op_flag++;
									if(op1_flag==0){
										operand1=array2num(num_array,index-1);
										op1_flag=1;;
									}
									index=0;
									break;
								case '=':
									lcd_send_data(key_pressed_current);
									if(op2_flag==0){
										operand2=array2num(num_array,index-1);
										op2_flag=1;;
									}
									index=0;
									if(op_flag==1 && op1_flag==1 && op2_flag==1)
									{
										switch(op)
										{
											case '+':
												result=operand1+operand2;
												flash_data_current=result;
												lcd_goto_pos(2,1);
												if(result<0)
												{
													lcd_send_data('-');
													result=result*(-1);
												}
												display_num((uint32_t)result);
												break;
											case '-':
												result=operand1-operand2;
												flash_data_current=result;
												lcd_goto_pos(2,1);
												if(result<0)
												{
													lcd_send_data('-');
													result=result*(-1);
												}
												display_num((uint32_t)result);
												break;
											case '*':
												result=operand1*operand2;
												flash_data_current=result;
												lcd_goto_pos(2,1);
												if(result<0)
												{
													lcd_send_data('-');
													result=result*(-1);
												}
												display_num((uint32_t)result);
												break;
											case '/':
												lcd_goto_pos(2,1);
												result=operand1/operand2;
											  flash_data_current=result;
												div=operand1;
												display_num(result);
												div = (div - result * operand2) * 10000 / operand2;
												delay(1); 
												result = div;
												if (result==0) 
														break;
												lcd_send_data('.');
												delay(1); 
												while(result < 1000) 
												{	
														lcd_send_data('0');
														delay(2);
														result=result*10;
												}
													display_num(div);												
										}
										do{
											delay(100);
											key_pressed_current=scan_keypad();
										}while(key_pressed_current==0);
										lcd_clear();
										lcd_goto_pos(1,1);
										op_flag=0;
										op1_flag=0;
										op2_flag=0;
										
										operand1=0;
										operand2=0;
									}
									else
									{
										lcd_goto_pos(2,4);
										lcd_send_string("Error");
										delay(1500);
										lcd_clear();
										lcd_goto_pos(1,1);
									}	
							}
				}
				if(key_pressed_current=='A'||key_pressed_current=='B')
					continue;
				else{
					key_pressed_current=0;
					flash_data_current=0;
				}
			}
			break;
		default:
				lcd_goto_pos(2,1);
			  lcd_send_string("Invalid option");
}
	return 1;
}



void ports_init(void)
{
	//Enable clcok for ports A,B,E and F
	SYSCTL_RCGC2_R = 0x33;//FE DCBA
	;
	;
	;
	//Unlock port A
	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTA_CR_R = 0xFC;
	//Initialize port A
	GPIO_PORTA_DEN_R = 0xFC;
	GPIO_PORTA_DIR_R = 0xC0;//1100 0000 - PA7 PA6 PA5 PA4 PA3 PA2 PA1 PA0
	GPIO_PORTA_PDR_R = 0x3C;
	
	//Unlock port F
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R = 0x0E;
	//Initialize port F
	GPIO_PORTF_AFSEL_R = 0x0;
	GPIO_PORTF_DEN_R = 0x0E;//0 0110 - PF4 PF3 PF2 PF1 PF0
	GPIO_PORTF_DIR_R = 0x0E;
	
	//Unlock port B
	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTB_CR_R = 0xF0;
	//Initialize port B
	GPIO_PORTB_AFSEL_R = 0x0;
	GPIO_PORTB_DEN_R = 0xF0;
	GPIO_PORTB_DIR_R = 0xF0;
	
	//Unlock port E
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_CR_R = 0x1C; //PE3  PE4
	//Initialize port E
	GPIO_PORTE_AFSEL_R = 0x0;
	GPIO_PORTE_DEN_R = 0x1C;
	GPIO_PORTE_DIR_R = 0x18;
	GPIO_PORTE_PDR_R = 0x04;
}

uint32_t power(uint32_t a,uint32_t b)
{ 
	int i;
	int ans=1;
	if(b==0)
		return 1;
	else{
		for(i=0;i<b;i++)
		{
			ans=ans*a;
		}
	}
		return ans;
}

uint32_t array2num(uint8_t *arr, int index)
{
	uint32_t operand=0;
	uint8_t place=0;
	while(index >= 0)
	{
		operand=operand+arr[index]*power(10,place);
		place++;
		index--;
	}
	return operand;
}

