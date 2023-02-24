CC=gcc

all: helper

helper: helper.c
	@$(CC) helper.c -o helper

rm: clean fresh

clean:
	@rm helper

fresh:
	@rm machines.dat
