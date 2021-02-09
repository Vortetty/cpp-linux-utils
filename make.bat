SET OUT=ls.exe
SET FILES=src/main.cpp
SET CFLAGS=-I. -std=c++17 -s -Os -static -fdata-sections -ffunction-sections -Wl,--gc-sections --static

mkdir -p bin
g++ -o bin/%OUT% %FILES% %CFLAGS%
