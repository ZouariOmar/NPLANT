all: Build

Build:
	gcc -o bin/main.exe main.c Functions.c -I ./Src/include -L ./Src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

build_run: Build
	build/sdl_app

clean:
	rm -rf Build/*