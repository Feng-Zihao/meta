

CC=clang
SRC_DIR=../src/
OBJ_DIR=../obj/
CFLAGS=-g -O0 -I$(SRC_DIR) -DCTEST_IGNORE_PASS
LDFLAGS=

.PHONY:  all clean

all: lex-test gram-test


lex-test: $(addprefix $(OBJ_DIR),lex.o lex-test.o)
	$(CC) $(LDFLAGS) $^ -o $@

gram-test: $(addprefix $(OBJ_DIR),lex.o gram.o gram-test.o)
	$(CC) $(LDFLAGS) $^ -o $@

$(addprefix $(OBJ_DIR),%.o): %.c *.h
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -f $(addprefix $(OBJ_DIR),lex-test.o)
	rm -f lex-test
