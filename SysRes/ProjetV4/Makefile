CC=gcc
CFLAGS=-pthread -I

INCLUDE=Headers

SRC=$(wildcard Sources/*.c)
BIN=THE_MIND

.PHONY=all clean

all: main.c $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $(BIN)
	./$(BIN)

format: main.c $(SRC)
	clang-format -i $^

clean:
	rm $(BIN)
