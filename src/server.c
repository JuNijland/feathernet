#ifdef __unix__
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <netinet/in.h>

	#define OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
	#include <winsock2.h>

	#define OS_WINDOWS
#endif

#include <stdio.h>
#include "transmit.h"

#ifndef IPPROTO_TCP
#define IPPROTO_TCP 0	
#endif

/**
 * create_serversock - Create a server socket connection
 * @port: The port of the socket to listen on
 * 
 * Returns the socket integer that you need as
 * a parameter to send and/or receive data
 * to/from one or several clients.
 */
int create_serversock(int port) 
{
	int serversock;
	struct sockaddr_in server;
#ifdef OS_WINDOWS
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
#ifdef FEATHER_DEBUG
		printf("ERROR: Failed to initialize Winsock2; err_code: %d\n",
					 WSAGetLastError());
#endif
		return -1;
	}
#endif
	serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serversock < 0) {
#ifdef FEATHER_DEBUG
		printf("ERROR: Failed to create a socket\n");
#endif
		return -1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);

    int bindsocket = 
        bind(serversock, (struct sockaddr *) &server, sizeof(server));

	if (bindsocket < 0) {
#ifdef FEATHER_DEBUG
		printf("ERROR: Failed to bind a socket.\n");
#endif
		return -1;
	}
	return serversock;
} 

/**
 * listen_serversock - Listens for incoming connections
 * @serversock: The socket where to listen on
 * @max_clients: The maximum amount of pending clients
 * @client_ip: A character array to store the ip from the client
 *
 * Returns the socket int of the client. This can be used
 * with send_data and receive_data to communicate with the
 * client
 */
int listen_serversock(int serversock, int max_clients, char *client_ip)
{
	int clientsock;
	struct sockaddr_in client;
	unsigned int clientlen = sizeof(client);
    memset(&client, '\0', clientlen);

	if (listen(serversock, max_clients) < 0) {
#ifdef FEATHER_DEBUG
		printf("ERROR: Failed to listen on serversocket\n");
#endif
		return -1;
	}
    clientsock = accept(serversock, (struct sockaddr *) &client, &clientlen);
	if (clientsock < 0) 
    {
#ifdef FEATHER_DEBUG
        printf("ERROR: Failed to accept client connection.\n");
#endif
        return -1;
    }
	strcpy(client_ip, inet_ntoa(client.sin_addr));

	return clientsock;
}
