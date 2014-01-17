#! /bin/bash

while true; do
    inotifywait -q -e close_write ./metaparser.y;
    clear;
    ./lemon metaparser.y;
    date
done;
