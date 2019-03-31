/*
 * eval.h
 *
 * Created: 3/20/2019 10:05:58 AM
 *  Author: steve
 */ 


#ifndef EVAL_H_
#define EVAL_H_


char get_char();
char get_char_and_move();  // gets this char and move pointer to next
int get_number();
double num_eval();// third level  () and number
double eval_term();  // second level * and /
double poly_eval();   // tree root  + and -

double eval(char * expression);


#endif /* EVAL_H_ */