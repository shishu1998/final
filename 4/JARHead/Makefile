all: client.out server.out

client.out: client.c
	gcc client.c -o client.out -l ncurses

server.out: server.c
	gcc server.c -o server.out -l ncurses

client:
	./client.out

server:
	./server.out
