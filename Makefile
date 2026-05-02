#!/bin/make -f

CFLAGS   := -std=gnu23 -O2 -Wall -Wextra -Wpedantic --preload-file resource --shell-file shell.html
CPPFLAGS := -Iinclude -L. -DPLATFORM_WEB
LDFLAGS  := \
        -s INITIAL_MEMORY=32MB \
        -s ALLOW_MEMORY_GROWTH=1 \
	-s STACK_SIZE=16MB \
	-s MAX_WEBGL_VERSION=2 \
	-s MIN_WEBGL_VERSION=2 \
	-s EXPORTED_RUNTIME_METHODS='["requestFullscreen"]' \
	-s USE_WEBGL2=1 \
	-s USE_GLFW=3 \
	-s ASSERTIONS=0 \
	-s SAFE_HEAP=0 \
	-s STACK_OVERFLOW_CHECK=0 \
	-s EMIT_EMSCRIPTEN_METADATA=0 \
	-s FORCE_FILESYSTEM=0

emancer.html: source/main.c $(wildcard source/*.c)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< libraylib.web.a $(LDFLAGS)

run: emancer.html
