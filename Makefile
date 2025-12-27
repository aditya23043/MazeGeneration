build: src/main.c
	gcc src/main.c -o bin/main -Wall -g -lSDL2

run: bin/main
	./bin/main
