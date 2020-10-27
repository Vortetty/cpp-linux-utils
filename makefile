CC=g++
CFLAGS=-I. -std=gnu++17

FILES=src/main.cpp
OUT=ft

$(OUT): $(FILES)
	mkdir -p bin
	$(CC) -o bin/$(OUT) $(FILES) $(CFLAGS)
	chmod +x bin/$(OUT)
