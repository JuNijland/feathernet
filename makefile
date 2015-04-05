CC = gcc
CFLAGS = -ansi -Wall

build: src/client.c src/close.c src/server.c src/transmit.c 
	$(CC) $(CFLAGS) -c src/client.c src/close.c src/server.c src/transmit.c src/utils.c 
	ar cr build/libfeathernet.a client.o close.o server.o transmit.o utils.o 
	rm -f *.o

http_client: examples/http_client.c
	$(CC) $(CFLAGS) -g -o build/http_client examples/http_client.c build/libfeathernet.a

clean:
	rm -f *~
	rm -f #*#
	rm -f *.o
