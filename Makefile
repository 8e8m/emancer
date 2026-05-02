#!/bin/make -f

DEBUG ?= 0
ifneq ($(DEBUG),0)
CFLAGS := -ggdb -fsanitize=address
endif

EMSCRIPTEN ?= 0

SHARED_CFLAGS   += -pipe -std=gnu23 -O2 -flto=auto -Wall -Wextra -Wpedantic
SHARED_CPPFLAGS := -D_FORTIFY_SOURCE=3

ifeq (${EMSCRIPTEN},0)
CFLAGS   := $(SHARED_CFLAGS)
CPPFLAGS := $(SHARED_CPPFLAGS)
LDFLAGS  := -lraylib -lglfw -lm

emancer: source/main.c $(wildcard source/*.c)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS)

run: emancer
	./emancer
else
# note: use emmake make
CC       := emcc

CFLAGS   := \
        $(SHARED_CFLAGS) \
        --preload-file resource \
        --shell-file raylib/src/shell.html

CPPFLAGS := -Iraylib/src $(SHARED_CPPFLAGS) -DPLATFORM_WEB

LDFLAGS  := \
        -s INITIAL_MEMORY=64MB \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s STACK_SIZE=4MB \
        -s MAX_WEBGL_VERSION=2 \
        -s MIN_WEBGL_VERSION=2 \
        -s ASYNCIFY=1 \
        -s EXPORTED_RUNTIME_METHODS='["requestFullscreen"]' \
        -s USE_WEBGL2=1 \
        -s USE_GLFW=3 \
        -s ASSERTIONS=0 \
        -s SAFE_HEAP=0 \
        -s STACK_OVERFLOW_CHECK=0 \
        -s EMIT_EMSCRIPTEN_METADATA=0 \
        -s FORCE_FILESYSTEM=0

emancer.html: source/main.c $(wildcard source/*.c)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< raylib/src/libraylib.web.a $(LDFLAGS)

run: emancer.html
	emrun emancer.html
endif
