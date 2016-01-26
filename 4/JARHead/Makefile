all: client.out server.out map.o
<<<<<<< HEAD

map.o: map.h map.c
	gcc -c map.c

client.out: client.c
	gcc client.c -o client.out -lncurses

server.out: server.c map.o
	gcc server.c map.o -o server.out -lncurses

clean:
	rm *.o
	rm *.out
=======

map.o: map.h map.c
	gcc -c map.c

client.out: client.c map.o
	gcc client.c map.o -o client.out -lncurses
>>>>>>> f77fcc45a5b5d702d0a2e4f4875a235af0fcc1ac

server.out: server.c map.o
	gcc server.c map.o -o server.out -lncurses

test.out: test.c map.o
	gcc test.c map.o -o test.out -lncurses

clean:
	rm *.o
	rm *.out

client: client.out
	./client.out

server: client.out
	./server.out

<<<<<<< HEAD
=======
test: test.out
	./test.out
>>>>>>> f77fcc45a5b5d702d0a2e4f4875a235af0fcc1ac
