#ifndef JMP_TXT_LOAD
#define JMP_TXT_LOAD

#include<stdio.h>
#include<malloc.h>

typedef struct{
	unsigned short int w;
	unsigned char h;
	unsigned int l;
	char* data;
} level;

level* load_level(char* file);

#endif
