BINS = "shader.c"

all: main

main:
	gcc -o game main.c $(BINS) -lSDL3 -lglew32 -lopengl32