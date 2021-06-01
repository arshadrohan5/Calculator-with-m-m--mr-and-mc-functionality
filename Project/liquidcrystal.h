#ifndef LIQUIDCRYSTAL_H
#define LIQUIDCRYSTAL_H


#include "tm4c123gh6pm.h"

//Function for delay
void delay(int mili);

void lcd_send_command(uint8_t command);

void lcd_send_data(uint8_t data);

void init_lcd(void);

void lcd_clear ( void );

void lcd_goto_pos ( unsigned int x, unsigned int y);

/* This function writes character string to LCD display . */
void lcd_send_string (char* ptr );

void display_num(unsigned int n);

#endif