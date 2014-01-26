

CC=clang
CFLAGS=-O0 
LDFLAGS=
OBJ_DIR=../obj/
YACC=bison
LEX=flex

.PHONY:  clean 
.IGNORE: lex.c parser.c


#all: $(addprefix $(OBJ_DIR),parser.o lex.o)
all: $(addprefix $(OBJ_DIR),gram.o lex.o)

#lemon: $(addprefix $(OBJ_DIR),lemon.o)
#    $(CC) $(LDFLAGS) $< -o $@

gram.c: gram.y
	$(YACC) -d -v -o $@ $^

gram.h: gram.c

lex.c: lex.l gram.h
	$(LEX) $^

$(addprefix $(OBJ_DIR),%.o): %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f lemon
	rm -f parser.c parser.h parser.out
	rm -f gram.output gram.c gram.h
	rm -f lex.c lex.h
