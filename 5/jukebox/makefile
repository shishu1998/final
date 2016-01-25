all: jukebox client 

jukebox: jukebox.c jukebox.h 
	gcc jukebox.c -o jukebox -g

client: client.c client.h player.h player.c
	gcc client.c player.c -o client -g

player: player.c
	gcc player.c -o player -g

clean:
	rm *~
	rm *#
