all: jukebox client player

jukebox: jukebox.c jukebox.h 
	gcc jukebox.c -o jukebox

client: client.c client.h
	gcc client.c -o client

player: player.c
	gcc player.c -o player

clean:
	rm *~
	rm *#
