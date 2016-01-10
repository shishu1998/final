##Nellie Spektor
##Loren Maggiore
##Rosalind Joyce

##Project Description:

We want to make something like iTunes that can be run in the terminal and accessed by multiple users to listen to music together. It would be almost like a jukebox where listeners could add a song to the communal queue. 

##User Interface:

	Users connect to a server to “tune in” and from there they can “request a song” or “list all available songs”
	Listed songs will have an appropriate ID used to request that song. 

##Technical Design: 

##How we are breaking down the project and who is responsible for which parts.
	song handling mechanism - use some code from tunez project
	network connection - reduce reuse recycle
	client requests to server
##Data Structures
		Arrays and Structs to organize the songs by artist and song name.
			also a list of songs to play next
##Algorithms (and methods) we will use and how
	Shared memory for song queue
	Semaphores to limit listeners
	Server to control music playing

##Timeline 
		Monday - Beginnings of server up and running with a library of loaded songs and the ability to play them
		Wednesday - Server side functionality for requests clients will make (ie suggested songs)
		Friday - Semaphores and server-client handshake interaction

		Next Monday - Client programs ability to receive songs from server, tune in and listen
		Next Wednesday - Client ability to request songs and exit on command

		Next Friday - Make a jazzy jukebox logo (key step)


