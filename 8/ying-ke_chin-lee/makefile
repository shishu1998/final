all: main server client writing control

main: main.c
	gcc -o main main.c

server: server.c
	gcc -o server server.c

client: client.c
	gcc -o client client.c

writing: writing.c
	gcc -o writing writing.c

control: control.c
	gcc -o control control.c

clean:
	rm main
	rm server
	rm client
	rm writing
	rm control

run:
	./main