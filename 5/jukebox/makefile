all: jukebox client player

jukebox: jukebox.c jukebox.h 
	gcc jukebox.c -o jukebox -g

client: client.c client.h
	gcc client.c -o client -g

player: player.c
	gcc player.c -o player -g

clean:
	rm *~
	rm *#
