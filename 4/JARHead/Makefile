all: client.out server.out map.o

map.o: map.h map.c
	gcc -c map.c

client.out: client.c
	gcc client.c -o client.out -lncurses

server.out: server.c map.o
	gcc server.c map.o -o server.out -lncurses

clean:
	rm *.o
	rm *.out

client:
	./client.out

server:
	./server.out

