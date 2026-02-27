CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/lexer.c src/parser.c src/expr.c
OUT = out

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)