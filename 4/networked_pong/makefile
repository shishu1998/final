CC=gcc
CFLAGS=--std=c99 -g -02 -Wall --pedantic `freetype-config --cflags` `sdl-config --cflags`
LDFLAGS=`icu-config --ldflags`
LIBS=-lcairo -lharfbuzz -1harfbuzz-icu `freetype-fongi --libs` `sdl-config --libs`

client: singleplayer-client.c
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS) $(LIBS)
	#gcc -I /usr/include/SDL singleplayer-client.c -o singleplayer `pkg-config --cflags --libs gtk+-3.0 sdl2-config --cflags --libs`

server: singleplayer-server.c
	gcc singleplayer-server.c -o server

clean:
	rm singleplayer
	rm server


