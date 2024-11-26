all: run

Build:
	gcc -o bin/main.exe main.c Functions.c -I ./Src/include -L ./Src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

run: Build
	./bin/main