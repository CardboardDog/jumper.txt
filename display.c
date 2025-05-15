#include<display.h>

static struct termios old, current;
static int flags;
void putch(int x, int y, char c){
	printf("\033[%d;%dH%c",x+1,y+1,c);
}

void display_start(){
	printf("\033[2J");
	tcgetattr(0,&old);
	current = old;
	current.c_lflag &= ~ICANON;
	current.c_lflag &= ~ECHO;
	tcsetattr(0,TCSANOW,&current);
	printf("\033[?25l");
	flags = fcntl(0,F_GETFL,0);
	fcntl(0,F_SETFL,flags|O_NONBLOCK);
}

void display_exit(){
	printf("\033[?25h");
	fcntl(0,F_SETFL,flags);
	tcsetattr(0,TCSANOW,&old);
}

void draw_level(level* world, unsigned char score, char lives){
	unsigned int tile = 0;
	for(unsigned char y = 0; y < world->h; y++){
		for(unsigned short x = 0; x < world->w; x++){
			putch(y,x,world->data[tile]);
			tile++;
		}
	}
	putch(world->h,0,'$');
	printf("%d",score);
	putch(world->h,world->w-1,lives+'0'); // hmmm... maybe putstr(x,y,str);
	putch(world->h,world->w-2,'x');
	putch(world->h,world->w-3,'@');
}
