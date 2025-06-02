build:
	gcc -Wall -std=c99 -Xpreprocessor -fopenmp \
	    -I/opt/homebrew/include \
	    -I/opt/homebrew/opt/libomp/include \
	    ./src/*.c -o game \
	    `sdl2-config --cflags --libs` \
	    -L/opt/homebrew/lib -L/opt/homebrew/opt/libomp/lib \
	    -lomp -lSDL2_image


run:
	./game

clean:
	rm game
