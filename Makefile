
CC=clang
CFLAGS=-c -O0 
LDFLAGS=

all: lemon

#test: grammar-test.o grammar.o
#    $(CC) $(LDFLAGS) $^ -o $@

%.o: %.c Makefile
	$(CC) $(CFLAGS) $< -o $@

lex.yy.c: meta.l
	flex meta.l

lemon: lemon.o
	$(CC) $(LDFLAGS) $^ -o $@

meta.h: lemon meta.y
	./lemon meta.y

clean:
	rm -f *.o
	rm -f meta.h meta.c meta.out lex.yy.c
	rm -f lemon
