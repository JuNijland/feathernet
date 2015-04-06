#ifndef FEATHERNET_H
#define FEATHERNET_H

/**
 * create_sock - Create a socket connection
 * @ip_address: The server's ip-address
 * @port: The port of the socket
 * 
 * Returns the socket integer that you need as
 * a parameter to send and/or receive data
 * from the targeted server, or -1 on error.
 */
int create_sock(char* ip_address, int port);

/**
 * create_serversock - Create a server socket connection
 * @port: The port of the socket to listen on
 * 
 * Returns the socket integer that you need as
 * a parameter to send and/or receive data
 * to/from one or several clients, or -1 on error.
 */
int create_serversock(int port);

/**
 * listen_serversock - Listens for incoming connections
 * @serversock: The socket where to listen on
 * @max_clients: The maximum amount of pending clients
 * @client_ip: A character array to store the ip from the client
 *
 * Returns the socket int of the client or -1 on error. This can
 * be used with send_data and receive_data to communicate with the
 * client
 */
int listen_serversock(int serversock, int max_clients, char *client_ip);

/**
 * close_sock - Removes the socket connection
 * @sock - Socket to delete
 *
 * Returns 0 on succes or -1 on failure
 */
int close_sock(int sock);

/**
 * send_data - Sends character array to socket server
 * @sock - Socket to send message to
 * @msg - Character array to send
 *
 * Returns 0 on succes or -1 on error
 */
int send_data(int sock, char* msg);

/**
 * receive_data - Receives message from socket
 * @sock - Socket to receive a message from
 * @buf - Character array to fill with the message
 * with a minimal length of buf_len + 1
 * @buf_len - Length of the buffer
 *
 * Returns the amount of bytes received on succes 
 * or -1 on error.
 */
int receive_data(int sock, char* buf, int buf_len);

/**
 * get_address - Get ip-adress by hostname
 * @hostname: The hostname of which you want to
 * receive the ip-adress
 * @char *ip: The char array where the ip-address
 * gets stored in
 *
 * Returns -1 on failure or 0 on succes.
 */
int get_ip(char *hostname, char *ip);

/**
 * validate_ip - Checks if a string is a valid ip-address
 * @ip_address: The string you want to validate
 *
 * Returns 1 if ip_address is valid and 0 if it is invalid.
 */
int validate_ip(char *ip_address);

#endif
