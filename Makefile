
CC=gcc
CFLAGS=-pedantic -Wall -Werror -std=c99
CFLAGS+=-g
#CFLAGS+=-march=native
#CFLAGS+=-o2

test: test.c
	$(CC) $(CFLAGS) -o bin/test test.c
	./bin/test

json: src/json/json.c src/json/json.h src/index.h
	$(CC) $(CFLAGS) -c src/json/json.c -o src/json/json.o

clean:
	rm src/json/json.o