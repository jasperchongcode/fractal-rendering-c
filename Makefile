.DEFAULT_GOAL := build
.PHONY: clean run

build:
	gcc -Wall -std=c99 -Xpreprocessor -fopenmp \
		-O3 -flto -march=native -funroll-loops \
	    -I/opt/homebrew/include \
	    -I/opt/homebrew/opt/libomp/include \
	    ./src/*.c -o main \
	    `sdl2-config --cflags --libs` \
	    -L/opt/homebrew/lib -L/opt/homebrew/opt/libomp/lib \
		-lomp -lSDL2_image

run:
	./main

CC = gcc

CFLAGS = -Wall -std=c99 -march=native -fopenmp
PFLAGS = -O3 -flto -funroll-loops
SDL_CFLAGS = $(shell sdl2-config --cflags)
LFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lm

linux: src/*.c
		$(CC) $(CFLAGS) $(PFLAGS) $(SDL_CFLAGS) $^ -o $@ $(LFLAGS)

clean:
	rm main linux
