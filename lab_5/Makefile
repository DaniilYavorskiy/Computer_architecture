CC = gcc
CFLAGS = -Wall -Werror

all: console test_comp test_term test_bigchars test_readkey 

console: main.o libmy.a
	$(CC) -o console main.o -L. -lmy

test_comp: test_comp.o libmy.a
	$(CC) -o test_comp test_comp.o -L. -lmy

test_term: test_term.o libmy.a
	$(CC) -o test_term test_term.o -L. -lmy

test_bigchars: test_bigchars.o libmy.a
	$(CC) -o test_bigchars test_bigchars.o -L. -lmy

test_readkey: test_readkey.o libmy.a
	$(CC) -o test_readkey test_readkey.o -L. -lmy

libmy.a: myInterface.o myTerm.o mySimpleComputer.o myBigChars.o myReadKey.o mySignal.o myCU.o myALU.o
	ar cr libmy.a $^

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.a console test_comp test_term test_bigchars test_readkey