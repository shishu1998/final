all: client.out server.out map.o

map.o: map.h map.c
	gcc -c map.c

client.out: client.c map.o
	gcc client.c map.o -o client.out -lncurses

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

test: test.out
	./test.out
