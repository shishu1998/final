all: main.o libraryf.o
	gcc main.o libraryf.o

libraryf.o: libraryf.c libraryf.h
	gcc -c libraryf.c

main.o: main.c libraryf.h
	gcc -c main.c

clean: 
	rm *.o;
	rm *~;

run: all
	./a.out 