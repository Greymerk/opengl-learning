all: main

main:
	gcc -o game main.c -lSDL3 -lglew32 -lopengl32