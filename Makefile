BINS = shader.c timer.c debug.c

all: main

main:
	gcc -o game main.c $(BINS) -lSDL3 -lglew32 -lopengl32
	
clean:
	rm game.exe