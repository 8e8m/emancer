#!/bin/make -f

CC := emcc
CFLAGS   := -std=gnu23 -Os -Wall -Wextra -Wpedantic --preload-file resource
CPPFLAGS := -Iinclude -L. -DPLATFORM_WEB
LDFLAGS  := -s USE_GLFW=3 -s ASYNCIFY --shell-file shell.html -s TOTAL_MEMORY=268435456 -s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=64MB -s MAX_WEBGL_VERSION=3 -s EXPORTED_RUNTIME_METHODS='["requestFullscreen"]' -s USE_WEBGL2=1

emancer.html: source/main.c $(wildcard source/*.c)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< libraylib.a $(LDFLAGS)

run: emancer.html
