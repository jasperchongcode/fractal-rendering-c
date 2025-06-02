build: 
	gcc -Wall -std=c99 ./src/*.c -o game `sdl2-config --cflags --libs`

run:
	./game 

clean:
	rm game
