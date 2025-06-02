build:
	gcc -Wall -std=c99 -Xpreprocessor -fopenmp \
	    -I/opt/homebrew/opt/libomp/include \
	    ./src/*.c -o game \
	    `sdl2-config --cflags --libs` \
	    -L/opt/homebrew/opt/libomp/lib -lomp

run:
	./game

clean:
	rm game
