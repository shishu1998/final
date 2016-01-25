all: server client

server: server.c server.h client_relations.c
	gcc -o server server.c client_relations.c

client: client.c client_relations.c
	gcc -o client client.c client_relations.c


