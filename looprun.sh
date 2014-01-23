#! /bin/bash

while true; do
    inotifywait -q -e modify ./src/{lex.l,parser.y} ./test/*.{c,h}
    clear;
    rm -f test/lex-test
    make
    echo "== Run  =="
    ./test/lex-test
    echo "== Stop =="
    date
done;
