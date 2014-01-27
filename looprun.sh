#! /bin/bash

while true; do
    inotifywait -q -e modify ./src/{lex.l,gram.y} ./test/*.{c,h}
    clear;
    make check
    date
done;
