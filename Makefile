CC = gcc
CFLAGS = -Wall -Wextra -g -O0 -Iinclude #-fsanitize=address 
#LDFLAGS = -fsanitize=address

SRC := $(wildcard src/*.c)
HDR := $(wildcard include/*.h)

OUT = clite

$(OUT): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -o $@ $(SRC)

all: $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean