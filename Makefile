
CC=clang
CFLAGS=-O0 
LDFLAGS=
SRC_DIR=./src/

.PHONY: build all

all: build

build:
	make -C src/
	make -C test/

clean:
	make -C src/ clean
	make -C test/ clean
	rm ./obj/*.o
