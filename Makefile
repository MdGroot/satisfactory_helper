CC=gcc
CFLAGS=-Wall -Wextra

all: helper

helper: helper.o funct.o
	@$(CC) $(CFLAGS) helper.o funct.o -o helper

helper.o: helper.c
	@$(CC) $(CFLAGS) helper.c -c

funct.o: funct.c funct.h
	@$(CC) $(CFLAGS) funct.c -c

rm: clean fresh

clean:
	@rm helper helper.o funct.o

fresh:
	@rm machines.dat
