all: client.o server.o 
	gcc -o typeracer client.o server.o

client.o: client.c client.h
	gcc -c client.c

server.o: server.c server.h
	gcc -c server.c

run:
	./typeracer

clean:
	rm *.o
	rm *~
	rm typeracer
