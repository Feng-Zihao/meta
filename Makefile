
CXX=clang++
CXXFLAGS=-c -O0 -std=c++11
LDFLAGS=-lgtest -lboost_regex

all: test

test: grammar-test.o grammar.o
	$(CXX) $(LDFLAGS) $^ -o $@
	./test

%.o: %.cc *.hpp Makefile
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o *.pyc
	rm -f test
