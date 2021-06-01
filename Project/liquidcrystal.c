#include "tm4c123gh6pm.h"
//Function for delay
void delay(int mili)
{
	int i, j;
	for (i=0;i<mili;i++)
	{
		// for 1 ms
		for (j=0;j<3840;j++)
		;
	}
}

void lcd_send_command(uint8_t command)
{
	GPIO_PORTF_DATA_R = 0x0; 
	GPIO_PORTB_DATA_R = command & 0xF0;
	
	//Pulse generator
	delay(1);
	GPIO_PORTF_DATA_R |= 0x08; 
	delay(1);
	GPIO_PORTF_DATA_R &= ~(0x08);
	delay(1);
	
	GPIO_PORTB_DATA_R = (command) << 4;
	//Pulse generator
	delay(1);
	GPIO_PORTF_DATA_R |= 0x08; 
	delay(1);
	GPIO_PORTF_DATA_R &= ~(0x08);
	delay(4);
	
}

void lcd_send_data(uint8_t data)
{
	GPIO_PORTF_DATA_R = 0x02;  //PF1 - Rs
	GPIO_PORTB_DATA_R = data & 0xF0;
	
	//Pulse generator
	delay(1);
	GPIO_PORTF_DATA_R |= 0x08;
	delay(1);
	GPIO_PORTF_DATA_R &= ~(0x08);
	delay(4);
	
	GPIO_PORTB_DATA_R = data << 4;
	//Pulse generator
	delay(1);
	GPIO_PORTF_DATA_R |= 0x08;
	delay(1);
	GPIO_PORTF_DATA_R &= ~(0x08);
	delay(4);
	GPIO_PORTF_DATA_R = 0;
}

void init_lcd(void)
{
	GPIO_PORTF_DATA_R = 0;
	delay (15) ; // Wait for approx . 15 ms
	// Configure LCD for required functionality
	lcd_send_command (0x02);
	lcd_send_command (0x28); // Function Set : 8 bit , 2 line
	lcd_send_command (0x10); // Set cursor
	lcd_send_command (0x0F); // Display ON , cursor ON
	lcd_send_command (0x06); // Entry mode
}

void lcd_clear ( void )
{
	lcd_send_command (0x01); // Clear display
	delay (2) ; // Delay for approx . 2 ms
	lcd_send_command (0x02); // Move cursor to home
	delay (2) ; // Delay for approx . 2 ms
}

void lcd_goto_pos ( unsigned int x, unsigned int y)
{
	unsigned int row_start_address [] = {0x80 , 0xC0 };
	// Move cursor to (x,y) location on display
	lcd_send_command ( row_start_address [x -1] + y - 1);
	delay (2) ; // Delay for approx . 2 ms
}
/* This function writes character string to LCD display . */
void lcd_send_string (char* ptr )
{
	while (* ptr ){
	lcd_send_data (* ptr );
	ptr ++;
	}
}
void display_num(uint32_t n)
{
	int i;
	uint8_t num[16]; 
	uint8_t count = 0;
	if(n == 0)  
	{
		lcd_send_data('0');
		return;
	} 
	while(n>0)
	 {
       num[count] = ( (n %10) + 48 );
       n /=10; 
			 count++;
   }
   for(i=count-1;i>=0;i--) 
   {
       lcd_send_data(num[i]);  
    }
}
