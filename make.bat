SET OUT=ls.exe
SET FILES=src/main.cpp
SET CFLAGS=-I. -std=c++17 -s -Os -static

mkdir -p bin
g++ -o bin/%OUT% %FILES% %CFLAGS%
