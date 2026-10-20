
CC = gcc
WIN_CC = x86_64-w64-mingw32-gcc

CFLAGS = -Wall -Wextra -g -O0 -Iinclude
# CFLAGS += -fsanitize=address
# LDFLAGS = -fsanitize=address

SRC := $(wildcard src/*.c)
HDR := $(wildcard include/*.h)

BUILD_DIR = build
LINUX_OUT = $(BUILD_DIR)/linux/clite
WIN_OUT = $(BUILD_DIR)/win/clite.exe

.PHONY: all linux win clean

# Build both targets
all: linux win

linux: $(LINUX_OUT)

win: $(WIN_OUT)

# Linux build
$(LINUX_OUT): $(SRC) $(HDR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

# Windows cross-build
$(WIN_OUT): $(SRC) $(HDR)
	mkdir -p $(dir $@)
	$(WIN_CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
	