

CC=clang
CFLAGS=-O0
LDFLAGS=
OBJ_DIR=../obj/
YACC=bison
LEX=flex


all: $(addprefix $(OBJ_DIR),lex.o gram.o)

gram.c: gram.y
	$(YACC) -d -v -o $@ $^

gram.h: gram.c

lex.c: lex.l gram.h
	$(LEX) $^
	# These 3 functions are to be called from bison.
	sed -i 's/static\ void\ yy_push_state/void\ yy_push_state/g' $@
	sed -i 's/static\ void\ yy_pop_state/void\ yy_pop_state/g' $@
	sed -i 's/static\ int\ yy_top_state/int\ yy_top_state/g' $@


$(addprefix $(OBJ_DIR),%.o): %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f lemon
	rm -f parser.c parser.h parser.out
	rm -f gram.output gram.c gram.h
	rm -f lex.c lex.h
