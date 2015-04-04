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
 * create_sock - Create a socket connection
 * @ip_address: The server's ip-address
 * @port: The port of the socket
 * 
 * Returns the socket integer that you need as
 * a parameter to send and/or receive data
 * from the targeted server.
 */
int create_serversock(int port) 
{
	int serversock;
	struct sockaddr_in server;
#ifdef OS_WINDOWS
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("ERROR: Failed to initialize Winsock2; err_code: %d\n",
					 WSAGetLastError());
		return -1;
	}
#endif
	serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serversock < 0) {
		printf("ERROR: Failed to create a socket\n");
		return -1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);

    int bindsocket = 
        bind(serversock, (struct sockaddr *) &server, sizeof(server));

	if (bindsocket < 0) {
		printf("ERROR: Failed to bind a socket.\n");
		return -1;
	}
	return serversock;
} 

/**
 * delete_serversock - Dispose the server socket
 * @sock: The socket that is getting deleted.
 */
void delete_serversock(int sock)
{
#ifdef OS_WINDOWS
	closesocket(sock);
 	WSACleanup();
#endif
#ifdef OS_UNIX
	close(sock);
#endif
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

	if (listen(serversock, max_clients) < 0) {
		printf("ERROR: Failed to listen on serversocket\n");
		return -1;
	}
    clientsock = accept(serversock, (struct sockaddr *) &client, &clientlen);
	if (clientsock < 0) 
    {
        printf("ERROR: Failed to accept client connection.\n");
        return -1;
    }
	client_ip = inet_ntoa(client.sin_addr);

	return clientsock;
}
