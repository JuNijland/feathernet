#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../headers/feathernet.h"

/* enable debug mode */
#define FEATHER_DEBUG
#define BUF_SIZE 32

void echo(char *ip_address, int port)
{
    int sock;
    char msg[] = "Hello echoserver!";
    char buf[BUF_SIZE + 1];

    sock = create_sock(ip_address, port);

    if (send_data(sock, msg) != 0) {
        printf("ERROR: data could not be send to the echo server.\n");
        exit(-1);
    }
    printf("Message send: %s\n", msg);

    /* receive data from the echo server */
    if (receive_data(sock, buf, BUF_SIZE) < 0) {
        printf("ERROR: there was an error while receiving data from "
                "the echo server.\n");
        exit(-1);
    }
    printf("Message received: %s\n", buf);

    close_sock(sock);
    printf("The connection with the server is closed.\n");
}

int main(int argc, char **argv)
{
    int port;
    char *ip_address;
    
    if (argc != 3) {
        printf("USAGE: ./echo_client IP_ADDRESS PORT\n");
        exit(-1);
    }

    if (!validate_ip(argv[1])) {
        printf("ERROR: The ip-address entered was invalid.\n"); 
        exit(-1);
    }

    ip_address = argv[1];

    if ((port = atoi(argv[2])) == 0 && port < 65536) {
        printf("ERROR: The port-number entered was invalid.\n");
        exit(-1);
    }

    echo(ip_address, port);
    return 0;
}
