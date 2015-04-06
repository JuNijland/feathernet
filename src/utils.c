#ifdef __unix__
	#include <arpa/inet.h>
	#include <string.h>
	#include <netdb.h>

	#define OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
	#include <winsock2.h>

	#define OS_WINDOWS
#endif

#include "debug.h"

/**
 * get_address - Get ip-adress by hostname
 * @hostname: The hostname of which you want to
 * receive the ip-adress
 * @char *ip: The char array where the ip-address
 * gets stored in
 *
 * Returns -1 on failure or 0 on succes.
 */
int get_ip(const char *hostname, char *ip)
{
    int i;
    struct hostent *he;
    struct in_addr **addr_list;
         
    if ((he = gethostbyname(hostname)) == NULL) {
        FEATHER_DBG_PRINT("ERROR: The hostname could not be resolved (1)\n");
        return -1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for (i = 0; addr_list[i] != NULL; i++) {
        strcpy(ip, inet_ntoa(*addr_list[i]) );
        return 0;
    }
     
    FEATHER_DBG_PRINT("ERROR: The hostname could not be resolved (2)\n");
    return -1;
}

/**
 * validate_ip - Checks if a string is a valid ip-address
 * @ip_address: The string you want to validate
 *
 * Returns 1 if ip_address is valid and 0 if it is invalid.
 */
int validate_ip(const char *ip_address)
{
    struct sockaddr_in sa;
    if (inet_pton(AF_INET, ip_address, &(sa.sin_addr))) 
        return 1;

    return 0;
}
