all: console test_comp test_term

console: main.o libmyTerm.a libmySimpleComputer.a libmyInterface.a 
	gcc -o console main.o -L. -l myTerm -l mySimpleComputer -l myInterface 

test_comp: test_comp.o libmyTerm.a libmySimpleComputer.a libmyInterface.a 
	gcc -o test_comp test_comp.o -L. -l myTerm -l mySimpleComputer -l myInterface 

test_term: test_term.o libmyTerm.a libmySimpleComputer.a libmyInterface.a 
	gcc -o test_term test_term.o -L. -l myTerm -l mySimpleComputer -l myInterface 


main.o: main.c
	gcc -c main.c

test_comp.o: test_comp.c
	gcc -c test_comp.c

test_term.o: test_term.c
	gcc -c test_term.c



libmyInterface.a: myInterface.o
	ar cr libmyInterface.a myInterface.o

libmyTerm.a: myTerm.o
	ar cr libmyTerm.a myTerm.o

libmySimpleComputer.a: mySimpleComputer.o
	ar cr libmySimpleComputer.a mySimpleComputer.o

myInterface.o: myInterface.c myInterface.h
	gcc -c myInterface.c

myTerm.o: myTerm.c myTerm.h
	gcc -c myTerm.c

mySimpleComputer.o: mySimpleComputer.c mySimpleComputer.h
	gcc -c mySimpleComputer.c


.PHONY: clean
clean:
	rm -f *.o *.a *.bin console test_comp test_term

