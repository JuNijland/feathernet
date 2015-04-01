#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 32

void Die(char *mess) 
{
	perror(mess); 
	exit(1); 
}

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in echoserver;
	char buffer[BUFFSIZE];
	unsigned int echolen;
	int recieved = 0;

	if (argc != 4) {
		fprintf(stderr, "USAGE: TCPecho <server_ip> <word> <port>\n");
		exit(1);
	}

	/* Create the TCP socket */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		Die("Failed to create socket");
	}

	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver)); 		/* Clear struct */
	echoserver.sin_family = AF_INET;					/* Internet/IP  */
	echoserver.sin_addr.s_addr = inet_addr(argv[1]);	/* IP adress 	*/
	echoserver.sin_port = htons(atoi(argv[3]));			/* Server port 	*/

	/* Establish connection */
	if (connect(sock,
				(struct sockaddr *) &echoserver,
				sizeof(echoserver)) < 0) {
		Die("Failed to connect with server");
	}

	/* Send the word to the server */
	echolen = strlen(argv[2]);
	if (send(sock, argv[2], echolen, 0) != echolen) {
		Die("Mismatch in number of sent bytes");
	}

	/* Recieve the word back from the server */
	fprintf(stdout, "Recieved: ");
	while (recieved < echolen) {
		int bytes = 0;
		if ((bytes = recv(sock, buffer, BUFFSIZE - 1, 0)) < 1) {
			Die("Failed to receive bytes from server");
		}

		recieved += bytes;
		buffer[bytes] = '\0';
		fprintf(stdout, "%s\n", buffer);
	}

	close(sock);		

	return 0;
}