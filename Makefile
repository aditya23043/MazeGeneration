build: src/main.c
	gcc src/main.c src/util/stack.c -o bin/main -Wall -g -lSDL2

run: bin/main
	./bin/main
