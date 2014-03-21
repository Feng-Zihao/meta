#! /bin/bash

while true; do
    inotifywait -q -e modify ./src/{lex.l,gram.y,*.h,*.cpp} ./test/*.cpp ./Makefile ./{src,test}/Makefile
    clear;
    make
    #make check
    date
done;
