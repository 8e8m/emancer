#!/bin/make -f

CFLAGS   := -std=gnu23 -O2 -Wall -Wextra -Wpedantic --preload-file resource --shell-file shell.html
CPPFLAGS := -Iinclude -L. -DPLATFORM_WEB
LDFLAGS  := -s INITIAL_MEMORY=32MB -s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=16MB -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s EXPORTED_RUNTIME_METHODS='["requestFullscreen"]' -s USE_WEBGL2=1 -s USE_GLFW=3

emancer.html: source/main.c $(wildcard source/*.c)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< libraylib.web.a $(LDFLAGS)

run: emancer.html
