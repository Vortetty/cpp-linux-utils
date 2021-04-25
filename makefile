CC=clang
CFLAGS=-I. -I./include -std=c++17 -s -Os -static -fdata-sections -ffunction-sections

ifeq ($(OS),Windows_NT)
fileSuffix=.exe
else
fileSuffix=
endif

all: ls pwd touch

ls:
	$(CC) -o bin/ls$(fileSuffix) $(CFLAGS) src/ls/main.cpp -Isrc/ls
	-chmod +x bin/ls$(fileSuffix)

pwd:
	$(CC) -o bin/pwd$(fileSuffix) $(CFLAGS) src/pwd/main.cpp
	-chmod +x bin/pwd$(fileSuffix)

touch:
	$(CC) -o bin/touch$(fileSuffix) $(CFLAGS) src/touch/main.cpp
	-chmod +x bin/touch$(fileSuffix)
