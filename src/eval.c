/*
 * eval.c
 *
 * Created: 3/20/2019 10:06:11 AM
 *  Author: steve
 */ 
#include "eval.h"
#include "lcd.h"

char * expression;

char get_char()
{
	return *expression;
}

char get_char_and_move()  // gets this char and move pointer to next
{
	char c = *expression;
	expression++;
	lcd_pos(1,9);
	lcd_puts2(expression);
	return c;
}

int get_number()
{
	int result = get_char_and_move() - '0';   // ASCII eval  <- this will move the pointer to the next char as well
	while (get_char() >= '0' && get_char() <= '9')  // only look at the this char, does not move point
	{
		result = 10*result + get_char_and_move() - '0'; // handle multiple digits
	}
	return result;
}

double num_eval() // third level  () and number 
{
	if (get_char() >= '0' && get_char() <= '9')
		return get_number();
	else if (get_char() == '(')
	{
		get_char_and_move(); // '('
		double result = poly_eval();
		get_char_and_move(); // ')'
		return result;
	}
	else if (get_char() == '-')
	{
		get_char_and_move();
		return (-1.0)*num_eval();
	}
	return 0.0; // error
}

double eval_term()  // second level * and /
{
	double result = num_eval();
	lcd_pos(1,2);
	lcd_puts2(expression);
	while (get_char() == '*' || get_char() == '/')
		if (get_char_and_move() == '*'){
			result *= num_eval();
		}
		else
			result /= num_eval();
	return result;
}

double poly_eval()   // tree root  + and -
{
	double result = eval_term(); 
	while (get_char() == '+' || get_char() == '-')
		if (get_char_and_move() == '+'){

			result += eval_term();
		}
		else
			result -= eval_term();
	return result;
}

double eval(char * new_expression)
{
	expression = new_expression;
	double result = poly_eval();
	return result;
}
