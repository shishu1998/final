DW APPROVED

##Nellie Spektor
##Loren Maggiore
##Rosalind Joyce

##Project Description:

We want to make something like iTunes that can be run in the terminal and accessed by multiple users to listen to music together. It would be almost like a jukebox where listeners could choose a song from the jukebox's library and listen to it. 

##User Interface:

	Users connect to a server to “tune in” and from there they can list all available songs or play a song
	Listed songs will have the appropriate ID used to request that song. 

##Technical Design: 

##How we are breaking down the project and who is responsible for which parts.
	Roz - Code for playing an mp3 file from the terminal (player.c)
	Loren - Server code (jukebox.c)
	Nellie - Client code (client.c)
##Data Structures
	Arrays and Structs to organize the songs by artist and song name.
##Algorithms (and methods) we will use and how
	Semaphores to limit listeners
	Server to control music playing
	Client to choose song and listen to music
	TCP connection
	
##Timeline 
	1/11 - Beginnings of server up and running with a library of loaded songs and the ability to play them
	1/13 - Server side functionality for requests clients will make (ie suggested songs)
	1/15 - Semaphores and server-client handshake interaction
	1/18 - Client programs ability to receive songs from server, tune in and listen
	1/20 - Client ability to request songs and exit on command
	1/22 - Make a jazzy jukebox logo (key step)
	1/26 - DONE

##TO RUN
     0. If using a linux machine:
     	 in terminal run$ sudo apt-get install mpg321
	 to install mpg321 which plays mp3 files on linux machines
     1. Run make
     2. In one terminal window, run ./jukebox
     3. In another terminal window, run ./client
     4. Follow instructions given by client to list songs, play a song, or exit
