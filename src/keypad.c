/*
 * keypad.c
 *
 * Created: 2/3/2019 10:17:03 AM
 *  Author: steve
 */ 
#include "keypad.h"

char convert(int raw){
	switch (raw){
		case 0:
			return '1';  
		case 1: 
			return '2';  
		case 2:
			return '3';  
		case 3:
			return '+';  
		case 4:
			return '4';  
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '-';
		case 8:
			return '7';
		case 9:
			return '8';
		case 10:
			return '9';
		case 11:
			return '*';
		case 12:
			return 'r';
		case 13:
			return '0';
		case 14:
			return 'b';  //backspace
		case 15:
			return '/';
		default:
			return '?';
	}
}

char getKey() { 
	for(int r=0; r<4; ++r)
		for(int c=0; c<4; ++c){
			if(is_pushed(r,c))
				return convert(c*4+r);
		}
	return '?';
}
/*
int getKey_multiple() {
	int pushed_keys[4];
	char numOfKeys = 0;
	for (int r=0; r<4; ++r)
		for(int c=0; c<4; ++c)
			if(is_pushed(r,c)){
				pushed_keys[++numOfKeys] = r*4+c; 
			}
	return pushed_keys;
}
*/

/*
1111 0000
row  col
*/

int is_pushed(int r, int c) {
	DDRC = 0;  // all c and r are input
	PORTC = 0;
	SET_BIT(DDRC,c);
	CLR_BIT(PORTC,c);
	SET_BIT(PORTC,r+4);
	avr_wait_10us(3);
	if(!GET_BIT(PINC,r+4))
		return 1;
	else
		return 0;
}