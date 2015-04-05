#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "../headers/feathernet.h"

/* enable debug mode */
#define FEATHER_DEBUG
#define BUF_SIZE 32

void echo(int port)
{
    int sock;
    int client; /* client socket */
    char buf[BUF_SIZE + 1];
    char client_ip[16];

    sock = create_serversock(port);

    /* listen for a client connection */
    client = listen_serversock(sock, 1, client_ip);
    
    /* receive data from the echo server */
    if (receive_data(client, buf, BUF_SIZE) < 0) {
        printf("ERROR: there was an error while receiving data from "
                "the client.\n");
        exit(-1);
    }
    printf("Message received from %s: %s\n", client_ip, buf);

    /* echo the data back to the client */
    if (send_data(client, buf) != 0) {
        printf("ERROR: data could not be send to the echo client.\n");
        exit(-1);
    }
    printf("Message has been send back to %s\n", client_ip);

    close_sock(client);
    printf("The connection with the client is closed.\n");
    close_sock(sock);
}

int main(int argc, char **argv)
{
    int port;

    if (argc != 2) {
        printf("USAGE: ./echo_server PORT\n");
        exit(-1);
    }

    if ((port = atoi(argv[1])) == 0 && port < 65536) {
        printf("ERROR: The port-number entered was invalid.\n");
        exit(-1);
    }

    echo(port);
    return 0;
}
