.PHONY : all, clean, mySimpleComputer.a, main

all: mySimpleComputer.a main

main:
	gcc main.c -L. -lfs -o simplePc

mySimpleComputer.a:
	gcc -c mySimpleComputer.c
	ar rc libfs.a mySimpleComputer.o
	ranlib libfs.a

clean:
	rm *.a *.o simplePc *.bin
