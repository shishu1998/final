all: server.c server.h client.c client.h values.h
	make server
	make client

server: server.c server.h values.h
	gcc -o server server.c

client: client.c client.h values.h
	gcc -o client client.c

#For when you're really lazy
git:
	git pull
	git commit -a -m "I was lazy and did this with a make command. I should feel bad and I probably borke something"
	git push 

#For when you're lazy, but you want to write a commit message
commit:
	git pull
	git add -u

#Clean up the directory
clear:
	touch bleh~
	touch blah.o
	rm *~
	rm *.o
	clear
