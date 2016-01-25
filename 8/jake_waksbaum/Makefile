CLANG := $(shell command -v clang >/dev/null 2>&1; echo $$?)
ifeq ($(CLANG), 0)
CC := clang
else
CC := gcc
endif

all: server client

SERVER_OBJECTS=server.o len_prefix.o shared.o
server: $(SERVER_OBJECTS)
	$(CC) -o server $(SERVER_OBJECTS)

CLIENT_OBJECTS=client.o len_prefix.o shared.o hostname.o
client: $(CLIENT_OBJECTS)
	$(CC) -o client $(CLIENT_OBJECTS)

%.o: %.c %.h
		$(CC) -c $<

clean:
		rm -f client server *.o
