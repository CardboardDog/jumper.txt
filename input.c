#include<input.h>

void get_input(input* player_input){
	char key = 0;
	for(int chunks = 0; chunks < 10; chunks++){ 
		// the for loop is so we can let the game catch up with the inputs 
		// this insure if the player is spamming or holding inputs,
		// there will be no delay while the game is trying to catch up
		// there is no "magic number" so ten ought to do
		// (these means the game can handle around 60 keys per second
		// since the game runs at roughly 6 FPS.)
		read(0,&key,1);
		switch(key){
			case 'a':
				player_input->d = -1;
				break;
			case 'd':
				player_input->d = 1;
				break;
			case 'l':
				player_input->j = 1;
				break;
		};
	}
}
