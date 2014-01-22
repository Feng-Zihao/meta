while true; do inotifywait -e modify lex-test.c; clear; make; ./lex-test; date; done
