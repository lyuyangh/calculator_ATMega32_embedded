/*
 * keypad.h
 *
 * Created: 2/3/2019 10:15:44 AM
 *  Author: Steven Hu & Steven He
 */ 

#include "avr.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

char getKey();
int is_pushed(int row, int col);



#endif /* KEYPAD_H_ */