#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/feathernet.h"

#define BUF_SIZE 4096
/* set debug mode */
#define FEATHER_DEBUG

char *build_http_request(const char *domainname) {
    /* very basic http request */
    char *query = "GET %s HTTP/1.0\r\n\r\n";
    /* strlen(query) -1 to discard the %s */
    char *result = malloc(strlen(domainname) + strlen(query)-1);
    /* complete the query with the domainname */
    sprintf(result, query, domainname);
    return result;
}

int get_content_length(const char *header) {
    /* get the content length of the html page from the header.
     * The length of the html doc starts 16 chars behind the string 
     * "Content-Length" hence the '+ 16' */
    char *tmp = strstr(header, "Content-Length") + 16;
    return atoi(tmp);
}

int main(int argc, char **argv) {
    int sock;
    char ip_address[16];
    char *domainname;
    char *query;
    char buf[BUF_SIZE + 1];

    int received_bytes;
    int content_length;
    
    /* exit if there are too much or no parameters */
    if (argc != 2) {
        printf("USAGE: ./http_client \"domainname\"\n");
        exit(-1);
    }

    domainname = argv[1];
    printf("Pulling data from \"%s\"...\n", domainname);

    /* check wether the domainname given as parameter
     * is correct / resolvable */
    if (get_ip(domainname, ip_address) < 0) {
        printf("ERROR: The domainname given was not "
               "correct or could not be resolved\n");
        exit(-1);
    }

    /* create a socket on port 80 (http) */
    sock = create_sock(ip_address, 80);

    /* create a http GET request */
    query = build_http_request(domainname);
    send_data(sock, query);

    /* receive the first block of data (including the 
     * html header) */
    received_bytes = receive_data(sock, buf, BUF_SIZE); 

    /* get the content length of the html page */
    content_length = get_content_length(buf);

    /* print the received bytes while you haven't reached
     * the full content length yet */
    printf("%s", buf);    
    while (received_bytes < content_length) {
        received_bytes += receive_data(sock, buf, BUF_SIZE);
        printf("%s", buf);
    }

    close_sock(sock);
    free(query);
    return 0;
}
