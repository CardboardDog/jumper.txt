#ifndef JMP_TXT_DISP
#define JMP_TXT_DISP

#include<load.h>
#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>

void draw_level(level*,unsigned char,char);
void putch(int x, int y, char c);
void display_start();
void display_exit();

#endif
