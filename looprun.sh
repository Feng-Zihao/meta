#! /bin/bash

while true; do
    inotifywait -q -e modify ./src/{lex.l,gram.y} ./test/*.{c,h}
    clear;
    rm -f test/lex-test
    #bison src/gram.y 2>&1 | head -n 20
    make
    #echo "== Run  =="
    #./test/lex-test
    #echo "== Stop =="
    date
done;
