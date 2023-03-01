CC=gcc
CFLAGS=-Wall -Wextra
SRC=src
BINDIR=bin
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN=$(BINDIR)/run

all: $(BIN)

$(BIN): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -r $(BIN) $(OBJ)/*

rm:
	@rm -r $(BINDIR)/* $(OBJ)/*
