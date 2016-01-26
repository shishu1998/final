CLANG := $(shell command -v clang >/dev/null 2>&1; echo $$?)
ifeq ($(CLANG), 0)
CC := clang
else
CC := gcc
endif

all: server client

server: server.o len_prefix.o shared.o
	$(CC) -o server server.o len_prefix.o shared.o

client: client.o len_prefix.h shared.o
	$(CC) -o client client.o len_prefix.o shared.o

%.o: %.c %.h
		$(CC) -c $<

clean:
		rm -f client server *.o
