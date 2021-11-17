CC = gcc
CFLAGS = -Wextra -Wall -Werror -std=c99 -pedantic -I

DEBUGFLAGS = -g $(CFLAGS)
BINDEBUG = debug

INC = ./header/

SRC = $(wildcard src/*.c)
OBJ = $(wildcard src/*.o)
BIN = game

TEST = tests/test.c
TESTOBJ = $(wildcard tests/*.o)
TESTBIN = test

.PHONY: clean all check debug

all: main.c $(SRC) 
	$(CC) $(CFLAGS) $(INC) $^ -o $(BIN)
	./$(BIN)

format: main.c $(SRC)
	clang-format -i $^

check: $(TEST) $(SRC)
	$(CC) $(CFLAGS) $(INC) $^ -o $(TESTBIN)
	./$(TESTBIN)

debug: main.c $(SRC)
	$(CC) $(DEBUGFLAGS) $(INC) $^ -o $(BINDEBUG)

clean:
	rm $(OBJ) $(BIN)

cleant:
	rm $(TESTBIN) $(TESTOBJ) 

cleand:
	rm $(BINDEBUG) $(OBJ)

cleana:
	rm $(OBJ) $(BIN) $(BINDEBUG) $(TESTOBJ) $(TESTBIN)
