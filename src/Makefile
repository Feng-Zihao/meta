

CC=clang
CFLAGS=-O0 
LDFLAGS=
OBJ_DIR=../obj/

.PHONY:  clean 
.IGNORE: lex.c parser.c


all: $(addprefix $(OBJ_DIR),parser.o lex.o)

lemon: $(addprefix $(OBJ_DIR),lemon.o)
	$(CC) $(LDFLAGS) $< -o $@

parser.c: parser.y lemon
	./lemon parser.y

lex.c: lex.l
	flex lex.l

$(addprefix $(OBJ_DIR),%.o): %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f lemon
	rm -f parser.c parser.h parser.out
	rm -f lex.c
