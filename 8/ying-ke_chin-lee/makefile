all: main server client control server_socket client_socket

main: main.c
	gcc -o main main.c

server: server.c
	gcc -o server server.c

client: client.c
	gcc -o client client.c

control: control.c
	gcc -o control control.c

server_socket: server_socket.c
	gcc -o server_socket server_socket.c

client_socket: client_socket.c
	gcc -o client_socket client_socket.c

clean:
	rm main
	rm server
	rm client
	rm control
	rm server_socket
	rm client_socket

run:
	./main