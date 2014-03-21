

CXX=clang++
SRC_DIR=../src/
OBJ_DIR=../obj/
CXXFLAGS=-g -O0 -I$(SRC_DIR) -std=c++11
LDFLAGS=-lgtest

.PHONY: all clean

all: lex-test gram-test

lex-test: $(addprefix $(OBJ_DIR),lex.o lex-test.o)
	$(CXX) $(LDFLAGS) $^ -o $@

gram-test: $(addprefix $(OBJ_DIR),lex.o gram.o gram-test.o)
	$(CXX) $(LDFLAGS) $^ -o $@

$(addprefix $(OBJ_DIR),%.o): %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f $(addprefix $(OBJ_DIR),lex-test.o)
	rm -f lex-test
