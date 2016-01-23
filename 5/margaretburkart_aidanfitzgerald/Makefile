all: server server_setup

server: server.c user.c dir.c network.c lib.h
	gcc server.c dir.c user.c network.c -o server

server_setup: server_setup.c
	gcc server_setup.c -o server_setup

client: client.c network.c lib.h
	gcc client.c network.c -o client

client_setup: client_setup.c
	gcc client_setup.c -o client_setup

# Creates server directory structure
mail.d: server_setup
	./server_setup

# Creates client directory structure
my_mail.d: client_setup
	./client_setup
