#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library

int main(int argc, char *argv[])
{
	WSADATA wsa;
	SOCKET s, new_socket;
	struct sockaddr_in server, client;
	int c;

	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code: %d\n", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d\n", WSAGetLastError());
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d\n", WSAGetLastError());
	}

	puts("Bind done");

	listen(s, 3);

	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s, (struct sockaddr *) &client, &c);
	if (new_socket == INVALID_SOCKET) {
		printf("Accept failed with error code: %d\n", WSAGetLastError());
	}

	puts("Connection accepted");

	closesocket(s);
	WSACleanup();

	return 0;
}