#!/bin/make -f

CC := emcc
CFLAGS   := -std=gnu23 -Os -Wall -Wextra -Wpedantic --preload-file resource -s USE_GLFW=3 -s ASYNCIFY --shell-file minshell.html -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=32MB -s MAX_WEBGL_VERSION=2
CPPFLAGS := -Iinclude -L. -DPLATFORM_WEB
LDFLAGS  :=

emancer.html: source/main.c $(wildcard source/*.c)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< libraylib.a

run: emancer.html
