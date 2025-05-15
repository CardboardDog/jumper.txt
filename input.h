#ifndef JMP_TXT_INPT
#define JMP_TXT_INPT

#include<termios.h>
#include<unistd.h>
#include<stdio.h>

typedef struct {
	char d; // direction
	unsigned char j; // jump
} input;

void get_input(input*);

#endif
