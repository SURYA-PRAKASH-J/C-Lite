CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/lexer.c src/parser.c src/expr.c src/AST.c src/interpreter.c
OUT = clite

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)