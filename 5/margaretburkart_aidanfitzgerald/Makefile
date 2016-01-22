all: server server_setup

server: server.c user.c dir.c network.c lib.h
	gcc server.c dir.c user.c network.c -o server

server_setup: server_setup.c
	gcc server_setup.c -o server_setup

# Creates server directory structure
mail.d: server_setup
	./server_setup
