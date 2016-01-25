Henry Filosa & Gregory Redozubov

Compilation:
	Compile with "make all"

Initializing Program:
	1. First run ./server. The server will check
	that all the files it needs are present and 
	creates semaphores.
	2. In another terminal run ./client to open the
	client.

Running Program: The program is interacted through the client
	1. Type 1 to log in or 2 to create a new account
	2. Enter username and password
	3. The following behavior will run on a loop
	4. The server will send any messages that are waiting
		Messages come in this format: [sender_name] : [message]
	5. You will then be asked to enter a user you wish to message
		That user does not need to exist yet, the server will still store the message
	6. Then simply enter the message you wish to send
		Steps 4-6 will now repeat
	
Exiting:
	1. Hit ctrl^c to exit server or client
	2. Server will close socket, ensure all children terminate and remove all semaphores.
