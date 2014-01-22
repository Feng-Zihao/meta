#! /bin/bash

while true; do
    inotifywait -q -e close_write ./{src,test}
    clear;
    make
    date
done;
