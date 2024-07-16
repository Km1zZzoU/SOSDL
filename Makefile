build:
	clear

	rm -rf ./gam

	gcc -Wall -std=c2x ./src/main.c `sdl2-config --libs --cflags` -lm -o gam

	./gam
