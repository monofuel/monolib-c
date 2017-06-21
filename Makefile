
CC=gcc
CFLAGS=-pedantic -Wall -Werror -std=c99
CFLAGS+=-g
#CFLAGS+=-march=native
#CFLAGS+=-o2

test: tests/test.c src/json/json.o src/string/string.o src/vector/vector.o src/list/list.o src/map/map.o
	$(CC) $(CFLAGS) -o bin/test tests/test.c \
		src/json/json.o \
		src/string/string.o \
		src/vector/vector.o \
		src/list/list.o \
		src/map/map.o
	valgrind --leak-check=full ./bin/test 
#	./bin/test

src/json/json.o: src/json/json.c src/json/json.h src/index.h
	$(CC) $(CFLAGS) -c src/json/json.c -o src/json/json.o

src/string/string.o: src/string/string.c src/string/string.h src/index.h
	$(CC) $(CFLAGS) -c src/string/string.c -o src/string/string.o

src/vector/vector.o: src/vector/vector.c src/vector/vector.h src/index.h
	$(CC) $(CFLAGS) -c src/vector/vector.c -o src/vector/vector.o

src/list/list.o: src/list/list.c src/list/list.h src/index.h
	$(CC) $(CFLAGS) -c src/list/list.c -o src/list/list.o

src/map/map.o: src/map/map.c src/map/map.h src/index.h
	$(CC) $(CFLAGS) -c src/map/map.c -o src/map/map.o

clean:
	rm src/json/json.o
	rm bin/test