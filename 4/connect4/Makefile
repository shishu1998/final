all: server client

server: server.c client_relations.c client_relations.h
	gcc -o server server.c client_relations.c

client: client.c client_relations.c client_relations.h
	gcc -o client client.c client_relations.c


