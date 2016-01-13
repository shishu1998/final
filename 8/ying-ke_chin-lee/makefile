all: main control server_socket client_socket

main: main.c
	gcc -o main main.c

control: control.c
	gcc -o control control.c

server_socket: server_socket.c
	gcc -o server_socket server_socket.c

client_socket: client_socket.c
	gcc -o client_socket client_socket.c

clean:
	rm main
	rm control
	rm server_socket
	rm client_socket

run:
	./main