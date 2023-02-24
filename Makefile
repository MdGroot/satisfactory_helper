CC=gcc
CFLAGS=-Wall -Wextra

all: helper

helper: helper.c
	@$(CC) $(CFLAGS) helper.c -o helper

rm: clean fresh

clean:
	@rm helper

fresh:
	@rm machines.dat
