
CXX=clang++
CXXFLAGS=-O0 -std=c++11
LDFLAGS=
SRC_DIR=./src/

.PHONY: build all

all: build

build:
	make -C src/
	make -C test/

check:	build
	@echo "===   Check Start  ==="
	./test/lex-test
	./test/gram-test
	@echo "=== Check Finished ==="

clean:
	make -C src/ clean
	make -C test/ clean
	rm ./obj/* -rf
