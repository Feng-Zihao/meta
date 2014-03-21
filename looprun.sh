#! /bin/bash

while true; do
    inotifywait -q -e modify ./src/{lex.l,gram.y} ./test/*.{c,h} ./Makefile ./{src,test}/Makefile
    clear;
    #make
    make check
    date
done;
