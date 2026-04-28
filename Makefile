#!/bin/make -f

CFLAGS   := -std=gnu23 -O2 -flto=auto -g -Wall -Wextra -Wpedantic
CPPFLAGS := 
LDFLAGS  := -lraylib -lglfw -lm

emancer: source/main.c $(wildcard source/*.c)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS)

run: emancer
	./emancer
