/*
 * p5 calculator.c
 *
 * Created: 3/20/2019 10:04:21 AM
 * Author : Steven Hu & Steven He
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "eval.h"
#include <stdio.h>

char expression_str[24]="";
char expression_buf[16];
unsigned int expression_len = 0;
char result_buf[16];
double result;

void init()
{
	lcd_init();
}

char isNum(char c){
	return c >= '0' && c <= '9';
}

char isOperator(char c){
	return c=='+' || c=='-' || c=='/' || c=='*';
}

char check_expression(){  // 0: invalid->backsapce  1: valid->evaluate  2:could be valid->don't evaluate until next
	if (expression_len>23)
		return 0;
	
	char prev = expression_str[0];
	for(int i = 1; i < expression_len; ++i){
		if(isOperator(prev) && isOperator(expression_str[i]))
			return 0;
		if(!isOperator(expression_str[i]) && !isNum(expression_str[i]))
			return 0;
		prev = expression_str[i];
	}
	if(isOperator(expression_str[expression_len-1]))
		return 2;
	return 1;
}
int main(void)
{
	init();

    /* Replace with your application code */
    while (1) 
    {
		char key = getKey();
		if(key != '?'){
			if(key=='r' && expression_len>0){
				expression_len = 0;
				expression_str[0] = '\0';
				result = eval(expression_str);
			}
			else if(key=='b' && expression_len>=1){
				expression_len--;
				expression_str[expression_len]='\0';
				result = eval(expression_str);

			} else if(key!='b') {
				if(isNum(key) || expression_len>=1 || key=='-'){
		
				expression_str[expression_len] = key;
				expression_len++;
				expression_str[expression_len] = '\0';
				char flag = check_expression();
				if(flag==1) // valid
					result = eval(expression_str);
				else if (flag == 0)
				{
					expression_str[--expression_len] = '\0';
					//give warning sound
				}
				}
			}
			lcd_clr();
			lcd_pos(0,0);
			lcd_puts2(expression_str);
			sprintf(result_buf,"ANS: %.2f",result);
			lcd_pos(1,0);
			lcd_puts2(result_buf);
			
		}
		avr_wait(300);
		
    }
}

