
CXX=clang++
CXXFLAGS=-c -g -O2 -std=c++11
LDFLAGS=-lgtest

all: test

test: grammar-test.o grammar.o
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cc *.hpp Makefile
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o *.pyc
	rm grammar-test
