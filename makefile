CC=g++
CFLAGS=-I. -std=c++17 -s -static -Ofast

FILES=src/main.cpp
OUT=ls

$(OUT): $(FILES)
	mkdir -p bin
	$(CC) -o bin/$(OUT) $(FILES) $(CFLAGS)
	chmod +x bin/$(OUT)
