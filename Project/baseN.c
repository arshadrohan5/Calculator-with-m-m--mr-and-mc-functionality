#include "liquidcrystal.h"
#include "keypad.h"
#include "baseN.h"

void dec_bin(int input)
 {
	 char in;
	 int disp[20],i=0,j=0;
	while(input>0)
	 {
		disp[i]=input%2;
		input/=2;
		i++;
	 }
	i--;
	lcd_clear();
	lcd_goto_pos(1,1);

	while(i>=0)
	{
		display_num(disp[i]);
		delay(1);
		i--;
	}
	 do{
		 in=scan_keypad();
	 }while(in==0);
	 
	}
///////////////////////////////////////
void dec_oct(int input)
 {
	 int disp[30];
	 int i=0,j=0;
	while(input>0)
	 {
		disp[i]=input%8;
		input/=8;
		i++;
	 }
	i--;
	lcd_clear();
	lcd_goto_pos(1,1);
	while(i>=0)
	{
		display_num(disp[i]);
		delay(1);
		i--;
	}
}
 /////////////////////////////////////////////
int bin_to_dec()
{
 	int decimal_value=0;
	int base=1,rem=0;
	int bin_value=0,j=0;
	char in;
	lcd_clear();
	lcd_goto_pos(1,1);
	lcd_send_string("Enter Number ");
	lcd_goto_pos(2,1);
	 while(1)
	{
	    do{
				in=scan_keypad();
			}while(in==0);
				
      if (in == '=') break;             
			bin_value = bin_value * 10 + (int)in - 48; 
			lcd_send_data(in);
			delay(1);
	}
	
	while(bin_value>0)
	{
		rem=bin_value%10;
		decimal_value=decimal_value+rem*base;
		bin_value/=10;
		base*=2;
	}
	lcd_clear();
	lcd_goto_pos(1,1);
	display_num(decimal_value);
	return decimal_value;
}
//////////////////////////////////////////////////
int oct_to_dec()
{
	int decimal_value=0;
	int base=1,rem=0;
	 int oct_value=0,j=0;
	 char in;
	lcd_clear();
	lcd_goto_pos(1,1);
	lcd_send_string("Enter Number ");	
	lcd_goto_pos(2,1);
	while(1)
	{
	    do{
				in=scan_keypad();
			}while(in==0);
			
      if (in == '=') break;             
				oct_value = oct_value * 10 + (int)in - 48; 
	     	lcd_send_data(in);
				delay(1);
	}
	while(oct_value>0)
	{
		rem= oct_value % 10;
		decimal_value=decimal_value+rem*base;
		oct_value/=10;
		base*=8;
	}
	lcd_clear();
	lcd_goto_pos(1,1);
	display_num(decimal_value);
	return decimal_value;
}/////////////////////////////////////////////
void decimal_to_hex(int decimalnum)
{
	int quotient=0,remainder=0;
	int i,j=0,k=0;
	char hexadecimal[20];
	char temp;
  lcd_clear();
	lcd_goto_pos(1,1);
	quotient=decimalnum;
	while(quotient!=0)
	{
		remainder=quotient%16;
		if(remainder<10)
		{
			hexadecimal[j++]=48+remainder;
		}
		else
			hexadecimal[j++]=55+remainder;
		quotient/=16;
	}

	for(i=j-1;i>=0;i--)
	{
		lcd_send_data(hexadecimal[i]);
		delay(1);
	}
	lcd_send_data(' ');
	lcd_send_command(0x10);
	do{
		temp=scan_keypad();
	}while(temp==0);
}
//////////////////////////////////////////
void oct_to_hex(){
	int num,i=0,j=0;
	num = oct_to_dec();
	lcd_clear();
	lcd_goto_pos(1,1);
	lcd_send_data(' ');
	lcd_clear();
	lcd_goto_pos(1,1);
	decimal_to_hex(num);	
	lcd_send_data(' ');
	lcd_clear();
	lcd_goto_pos(1,1);
}
///////////////////////////
void bin_to_hex(){	
	int num,i=0,j=0;
	num = bin_to_dec();
	lcd_clear();
	lcd_goto_pos(1,1);
	
	decimal_to_hex(num);	
	lcd_clear();
	lcd_goto_pos(1,1);
}
/////////////////////////////////
void bin_to_oct(){
	int num,i=0,j=0;
	char temp;
	num = bin_to_dec();
	lcd_clear();
	lcd_goto_pos(1,1);
	dec_oct(num);
	do{
		temp=scan_keypad();
	}while(temp==0);
	lcd_clear();
	lcd_goto_pos(1,1);
}
/////////////////////////////
void oct_to_bin()
{
	int num,i=0,j=0;
	char temp;
	num = oct_to_dec();
	lcd_clear();
	lcd_goto_pos(1,1);
	dec_bin(num);
	do{
		temp=scan_keypad();
	}while(temp==0);
	lcd_clear();
	lcd_goto_pos(1,1);	
}
///////////////////////////////////////
void baseN(void){
	int i=0;
	char choice1,choice2;
	while(1){
	lcd_clear();
	lcd_goto_pos(1,1);
	lcd_send_string("From? ");
	lcd_send_string("1.Decimal");
	lcd_goto_pos(2,1);
	i=0;

	lcd_send_string("2.Binary ");
	
	lcd_send_string("3.Octal");
	
	do{
		choice1=scan_keypad();
	}while(choice1==0);

	if(choice1 == '1'){
	lcd_clear();
	lcd_goto_pos(1,1);
	lcd_send_string("To?  ");
  
	lcd_send_string("1.Binary");
	
	lcd_goto_pos(2,1);
	lcd_send_string("2.Hex   ");
	
	lcd_send_string("3.Octal");
  }
	
	if(choice1 == '2'){
	lcd_clear();
	lcd_goto_pos(1,1);
	lcd_send_string("To? ");
  
	lcd_send_string("1.Decimal");
	lcd_goto_pos(2,1);
	
	lcd_send_string("2.Hex  ");
	
	lcd_send_string("3.Octal");
  }
	
	if(choice1 == '3'){
	lcd_clear();
	lcd_goto_pos(1,1);
	lcd_send_string("To? ");

	lcd_send_string("1.Decimal");
	lcd_goto_pos(2,1);
	lcd_send_string("2.Hex  ");
	
	lcd_send_string("3.Binary");
  }
	
	do{
		choice2=scan_keypad();
	}while(choice2==0);
	
	if(choice1 == '1')
	{
		if(choice2 == '1')
		{
			char in;
	 int i=0;
	 int answer;
	 lcd_clear();
	 lcd_goto_pos(1,1);
	 lcd_send_string("Enter Number ");
	 lcd_goto_pos(2,1);
	 while(1)
	{
	    do{
					in=scan_keypad();
	      }while(in==0);
			
      if (in == '=') break;             
			answer = answer * 10 + (int)in - 48; 
	   	lcd_send_data(in);
			delay(1);
	}
			dec_bin(answer);
		}
		if(choice2 == '2')
		{
			int decimalnum;
	    char in;
			lcd_clear();
	    lcd_goto_pos(1,1);
			lcd_send_string("Enter Number ");
			lcd_goto_pos(2,1);
	    while(1)
	{
					do{
							in=scan_keypad();
	          }while(in==0);
          if (in == '=') break;             
					decimalnum = decimalnum * 10 + (int)in - 48; 
					lcd_send_data(in);
					delay(1);
	}
			decimal_to_hex(decimalnum);
	
		}
		if(choice2 == '3')
		{
		char in;
		int i=0;
		int answer;
		lcd_clear();
	  lcd_goto_pos(1,1);
		lcd_send_string("Enter Number ");
		lcd_goto_pos(2,1);
	 while(1)
	{
	    do{
					in=scan_keypad();
	      }while(in==0);
			
      if (in == '=') break;             
			answer = answer * 10 + (int)in - 48; 
	   	lcd_send_data(in);
			delay(1);
	}
			dec_oct(answer);
			do{
					in=scan_keypad();
	      }while(in==0);
		}
	}
	if(choice1 == '2')
	{
		char in;
		if(choice2 == '1')
		{
			bin_to_dec();
			do{
					in=scan_keypad();
	      }while(in==0);
		}
		if(choice2 == '2')
		{
			bin_to_hex();
		}
		if(choice2 == '3')
		{
			bin_to_oct();
		}
	}
	if(choice1 == '3')
	{
		char in;
		if(choice2 == '1')
		{
			oct_to_dec();
			do{
					in=scan_keypad();
	      }while(in==0);
		}
		if(choice2 == '2')
		{
			oct_to_hex();
		}
		if(choice2 == '3')
		{
			oct_to_bin();
		}
	}
	}
	
}
