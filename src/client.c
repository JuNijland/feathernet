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
#include "debug.h"

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
 * from the targeted server, or -1 on error.
 */
int create_sock(const char* ip_address, int port) 
{
	int sock;
	struct sockaddr_in serversock;
#ifdef OS_WINDOWS
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		FEAHTER_DBG_PRINT(("ERROR: Failed to initialize Winsock2;"
                    "err_code:%d\n", WSAGetLastError()));
		return -1;
	}
#endif
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock < 0) {
		FEATHER_DBG_PRINT("ERROR: Failed to create a socket\n");
		return -1;
	}

	memset(&serversock, 0, sizeof(serversock));
	serversock.sin_family = AF_INET;
	serversock.sin_addr.s_addr = inet_addr(ip_address);
	serversock.sin_port = htons(port);
    int connected = 
        connect(sock, (struct sockaddr *) &serversock, sizeof(serversock));
	if (connected < 0) {	
		FEATHER_DBG_PRINT(("ERROR: Failed to connect with server %s:%d\n", 
				ip_address, port));
		return -1;
	}
	return sock;
}

