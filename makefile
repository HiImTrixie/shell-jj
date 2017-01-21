CC = gcc
FILES = main.c build_in.c shell.c functions.c
OUT = PonyShell

build: $(FILES)
	$(CC) -o $(OUT) $(FILES)

run: PonyShell
	env PATH="bin:/usr/bin" ./PonyShell

clean:
	rm PonyShell

rebuild: clean build
