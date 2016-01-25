run: ./interface

./interface: interface.o
	gcc -o interface interface.o -lncurses

interface.o: interface.c
	gcc -c interface.c

clean:
	rm ./interface
	rm interface.o
