client: singleplayer-client.c
	gcc -I /usr/include/SDL singleplayer-client.c -o singleplayer `pkg-config --cflags --libs gtk+-3.0`

server: singleplayer-server.c
	gcc singleplayer-server.c -o server

clean:
	rm singleplayer
	rm server
