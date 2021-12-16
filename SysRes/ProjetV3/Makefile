CC = gcc
CFLAGS = -I

DEBUGFLAGS = -g $(CFLAGS)
BINDEBUG = debug

INC = ./Header/

SRC = $(wildcard Sources/*.c)
OBJ = $(wildcard Sources/*.o)
BIN = game

TEST = tests/test.c
TESTOBJ = $(wildcard tests/*.o)
TESTBIN = test

.PHONY: clean all check debug

all: main.c $(SRC) 
	$(CC) $(CFLAGS) $(INC) $^ -o $(BIN)
	./$(BIN) 2

format: main.c $(SRC)
	clang-format -i $^

check: $(TEST) $(SRC)
	$(CC) $(CFLAGS) $(INC) $^ -o $(TESTBIN)
	./$(TESTBIN)

debug: main.c $(SRC)
	$(CC) $(DEBUGFLAGS) $(INC) $^ -o $(BINDEBUG)

serv: serveur.c $(SRC)
	$(CC) $(CFLAGS) $(INC) -pthread $^ -o Serveur
	./Serveur

client: client.c
	$(CC) $(CFLAGS) $(INC) $^ -o Client
	./Client

clean:
	rm $(OBJ) $(BIN)

cleant:
	rm $(TESTBIN) $(TESTOBJ) 

cleand:
	rm $(BINDEBUG) $(OBJ)

cleana:
	rm $(OBJ) $(BIN) $(BINDEBUG) $(TESTOBJ) $(TESTBIN)
