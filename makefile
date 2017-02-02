CC=gcc
CFLAGS += -Wall
CFLAGS += -I$(INCLUDE) 
CFLAGS += -std=gnu99
CFLAGS += -lreadline # for readline
CFLAGS += -O1        # release

SRC=./src
OBJ=./obj
INCLUDE=./include


install:$(OBJ)/main.o $(OBJ)/scan.o $(OBJ)/build_in.o \
	$(OBJ)/readline.o $(OBJ)/execute.o $(OBJ)/errorprocess.o \
	$(OBJ)/parse.o $(OBJ)/functions.o
	$(CC) $(CFLAGS) $^ -o PonyShell

$(OBJ)/main.o:$(SRC)/main.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ)/scan.o:$(SRC)/scan.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ)/build_in.o:$(SRC)/build_in.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/readline.o:$(SRC)/readline.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/execute.o:$(SRC)/execute.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/errorprocess.o:$(SRC)/errorprocess.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/parse.o:$(SRC)/parse.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/functions.o:$(SRC)/functions.c
	$(CC) $(CFLAGS) -c $< -o $@
run: PonyShell
	env PATH="bin" ./PonyShell

clean:
	rm -f $(OBJ)/* 
	rm -f PonyShell 

