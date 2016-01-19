Henry Filosa & Gregory Redozubov

Compilation:
	Simply compile with "make all"

Initializing Program:
	1. First run ./server. The server will check
	that all the files it needs are present and 
	creates semaphores.
	2. In another terminal run ./client to open the
	client.

Running Program: The program is interacted through the client
	1. Type 1 to log in or 2 to create a new account
	2. Enter username and password
	3. The client will forward any messages on to you that are queued
	4. The client will begin looping, asking for receipient and message
