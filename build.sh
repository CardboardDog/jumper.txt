gcc -c main.c -I. -g
gcc -c load.c -I. -g
gcc -c update.c -I. -g
gcc -c display.c -I. -g
gcc -c input.c -I. -g
gcc -o jumper.elf main.o load.o update.o display.o input.o -g
