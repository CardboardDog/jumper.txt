#include<jumper.h>
int main(int argc, char** argv){
	unsigned char export_result = 0;
	if(argc < 2){
		printf("JUMPER.TXT - A GAME BY EN\nusage: jumper [FILE]\nusage: jumper [LEVEL] [RESULTS]\n");
		return -1;
	}else if(argc == 3)
		export_result = 1;
	level* world = load_level(argv[1]);
	unsigned char score = 0;
	char lives = 3;
	display_start();
	input player_input;
	player_input.d = 1;
	player_input.j = 0;
	while(lives){
		get_input(&player_input);
		char result = update_level(&player_input,world);
		switch(result){
			case 3:
				// also should be a function
				putch(world->h/2,(world->w/2)-6,' ');
				printf("[You Win!] \n");
				sleep(5);
				if(export_result){
					FILE* save_score = fopen(argv[2],"w");
					unsigned int block = 0;
					for(unsigned short x = 0; x < world->h; x++){
						for(unsigned char y = 0; y < world->w; y++){
							fputc(world->data[block],save_score);
							block++;
						}
						fputc('\n',save_score);
					}
					fprintf(save_score,"score: %d\nlives: %d\n",score,lives);
					fputc('\0',save_score);
					fclose(save_score);
				}
				free(world->data);
				free(world);
				goto exit_game;
			case 2:
				score += 10;
				break;
			case 1:
				score++;
				break;
			case -1:
				//refractor to be a function.
				lives--;
				if(lives==0)
					goto exit_game; // not another goto!
				putch(world->h/2,(world->w/2)-5,' '); // need putstr(x,y,c);
				printf("[Ouch!] \n"); // remember: \n flushes the buffer!
				free(world->data);
				free(world);
				world = load_level(argv[1]);
				player_input.d = 1;
				player_input.j = 0;
				score = 0;
				sleep(3);
			default:
				break;
		};
		draw_level(world,score,lives);	
		update_delay();
	}
	exit_game:
	display_exit();
	printf("\n");
}
