

CC=clang
SRC_DIR=../src/
OBJ_DIR=../obj/
CFLAGS=-O0 -I$(SRC_DIR)
LDFLAGS=

.PHONY:  all clean

all: lex-test


lex-test: $(addprefix $(OBJ_DIR),lex-test.o lex.o)
	$(CC) $(LDFLAGS) $^ -o $@


$(addprefix $(OBJ_DIR),%.o): %.c *.h
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -f $(addprefix $(OBJ_DIR),lex-test.o)
	rm -f lex-test
