all: client.out server.out

test: test.c
	gcc test.c -o test.out -lncurses

test2: test2.c
	gcc test2.c -o test2.out -lncurses

client.out: client.c
	gcc client.c -o client.out -lncurses

server.out: server.c
	gcc server.c -o server.out -lncurses

client:
	./client.out

server:
	./server.out
