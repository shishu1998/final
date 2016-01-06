all: main server client

main: main.c
	gcc -o main main.c

server: server.c
	gcc -o server server.c

client: client.c
	gcc -o client client.c

clean:
	rm main
	rm server
	rm client

run:
	./main