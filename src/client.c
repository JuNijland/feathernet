#ifdef __unix__
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <netinet/in.h>

	#define OS_UNIX	1
#elif defined(_WIN32) || defined(WIN32)
	#include <winsock2.h>

	#define OS_WINDOWS 1
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
int create_sock(char* ip_address, int port) 
{
	int sock;
	struct sockaddr_in serversock;
#ifdef OS_WINDOWS
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("ERROR: Failed to initialize Winsock2; err_code:%d\n", WSAGetLastError());
		return -1;
	}
#endif
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

#ifdef OS_WINDOWS
	if (sock == INVALID_SOCKET) {
		printf("ERROR: Failed to create a socket\n");
		return -1;
	}
#elif OS_UNIX
	if (sock < 0) {
		printf("ERROR: Failed to create a socket\n");
		return -1;
	}
#endif

	memset(&serversock, 0, sizeof(serversock));
	serversock.sin_family = AF_INET;
	serversock.sin_addr.s_addr = inet_addr(ip_address);
	serversock.sin_port = htons(port);

	if (connect(sock,
				(struct sockaddr *) &serversock,
				sizeof(serversock)) < 0) {	
		/* error */
		printf("ERROR: Failed to connect with server %s:%d\n", 
				ip_address, port);
		return -1;
	}

	return sock;
}

/**
 * delete_sock - Removes the socket connection
 * @sock - Socket to delete
 */
void delete_sock(int sock)
{
#ifdef OS_WINDOWS
	closesocket(sock);
 	WSACleanup();
#elif OS_UNIX
	close(sock);
#endif
}

int main(int argc, char *argv[])
{
	char *c = "95.211.234.42";
	int port = 80;

	int sock = create_sock(c, port);

	char *msg = "GET / HTTP/1.1\r\n\r\n";
	send_data(sock, msg);

	char buf[2000];
	receive_data(sock, buf, 2000);
	printf("%s\n", buf);
	return 0;
}
