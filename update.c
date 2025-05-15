#include<update.h>

char player_velocity = -1;

#define tile_not_ground(tile) (tile == ' ' || tile == 'O' || tile == '$') // for falling tiles (they can collide with spikes)
#define not_ground(tile) (tile == ' ' || tile == 'O' || tile == '$' || tile == 'V' || tile == '^' || tile == '>' || tile == '<' || tile == '|' || tile == '.') // eww...
#define is_ground(tile) (tile != ' ' && tile != 'O' && tile != '$' && tile != 'V' && tile != '^' && tile != '>' && tile != '<' && tile != '|' && tile != '.')

void update_delay(){
	usleep(150000);
}

char interact_level(input* player_input, level* world, unsigned int* position){
	char skip = 0;
	for(unsigned int block = 0; block < world->l; block++){
		char tile = world->data[block];
		char next;
		char fall;
		switch(tile){
			case '<':
				next = world->data[block-1];
				fall =	world->data[block-1+world->w];
				if(is_ground(next) || not_ground(fall)){ 
					world->data[block] = '>';
					break;
				}
				if(next == '@')
					return -1;
				world->data[block] = ' ';
				world->data[block-1] = '<';
				break;
			case '>':
				if(skip){
					skip = 0;
					break;
				}
				next = world->data[block+1];
				fall =	world->data[block+1+world->w];
				if(is_ground(next) || not_ground(fall)){ 
					world->data[block] = '<';
					break;
				}
				if(next == '@')
					return -1;
				world->data[block] = ' ';
				world->data[block+1] = '>';
				skip = 1;
				break;
			case '+':
				if(world->data[block-world->w] == '@')
					world->data[block] = 'x';
				break;
			case 'x':
				world->data[block] = '-';
				break;
			case '-':
				next = world->data[block+world->w];
				if(next == '@'){
					world->data[block] = ' ';
					return 0; // skip the fram idk
				}else
					if(tile_not_ground(next)){
						world->data[block] = ' ';
						world->data[block+world->w] = '-';
					}else
						world->data[block] = ' ';
				break;
			case '@':
				*position = block;
			default:
				break;
		};
	}
	return 0;
}

char update_level(input* player_input, level* world){
	unsigned int player_position = 0;
	char interaction = interact_level(player_input,world,&player_position);
	unsigned int new_player = player_position;
	if(interaction < 0)
		return -1;
	// now move the player
	char examine = world->data[player_position+world->w];
	if(is_ground(examine)){ // refractor please
		if(player_input->j){	
			player_velocity = 1;
			player_input->j = 0;
		}
	}
	else if(player_velocity == -1)
		new_player += world->w;
	if(player_velocity != -1){
		player_velocity--;
		examine = world->data[new_player-world->w];
		if(not_ground(examine)){ 
			new_player -= world->w;
		}
	}
	examine = world->data[new_player+player_input->d];
	if(not_ground(examine))
		new_player += player_input->d;
	// collectables, static spikes, goal post
	switch(world->data[new_player]){
		case '^':
		case 'V':
		case '>':
		case '<':
			return -1;
		case 'O':
			interaction = 1;
			break;
		case '$':
			interaction = 2;
			break;
		case '.':
		case '|':
			return 3;
	};
	// set tile
	world->data[player_position] = ' ';
	world->data[new_player] = '@';
	return interaction;
}
