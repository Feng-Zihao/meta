

CXX=clang++
CXXFLAGS=-O0 -std=c++11
LDFLAGS=
OBJ_DIR=../obj/
YACC=bison
LEX=flex


all: $(addprefix $(OBJ_DIR),lex.o gram.o semt.o)

gram.cpp: gram.y
	$(YACC) -d -v -o $@ $^

gram.h: gram.cpp
	mv gram.hpp $@

lex.cpp: lex.l gram.h
	$(LEX) $<
	sed -i 's/register//g' $@

$(addprefix $(OBJ_DIR),%.o): %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f gram.output gram.cpp gram.h
	rm -f lex.cpp lex.h
