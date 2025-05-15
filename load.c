#include<load.h>

level* load_level(char* file){
	FILE* load_file = fopen(file,"r");
	char* examination_buffer = malloc(1*sizeof(char)); // we will extend it later :)
	unsigned int length = 1;
	unsigned short longest_line = 0;
	unsigned short current_line = 1;
	unsigned char height;
	while(1){	
		char tile = fgetc(load_file);
		if (longest_line < current_line) longest_line = current_line-1;
		switch (tile){
			case '\n':
				current_line = 1;
				height++;
				break;
			case EOF:
				goto end_of_file; // i promise i will refractor later 
			default:
				current_line++;
				break;
		};
		examination_buffer = realloc(examination_buffer,length*sizeof(char));
		examination_buffer[length-1] = tile;
		length++;
	}
	end_of_file: // no
	fclose(load_file);
	// code below fills in empty space
	char* data_buffer = malloc(longest_line*height*sizeof(char));
	current_line = 0;
	unsigned int buffer_cursor = 0;
	for(int block = 0; block < length; block++) {
		char tile = examination_buffer[block];
		if(tile != '\n'){
			data_buffer[buffer_cursor] = tile;
			buffer_cursor++;
			current_line++;
		}
		else if (current_line < longest_line){
			for(int filler = 0; filler < (longest_line-current_line); filler++){
				data_buffer[buffer_cursor] = ' ';
				buffer_cursor++;
			}
			current_line = 0;
		}
	}
	free(examination_buffer);
	level* world = malloc(sizeof(level));
	world->w = longest_line;
	world->h = height;
	world->l = (unsigned int)longest_line*(unsigned int)height;
	world->data = data_buffer;
	return world;
}
