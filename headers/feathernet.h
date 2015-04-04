#ifndef FEATHERNET_H
#define FEATHERNET_H

/**
 * create_sock - Create a socket connection
 * @ip_address: The server's ip-address
 * @port: The port of the socket
 * 
 * Returns the socket integer that you need as
 * a parameter to send and/or receive data
 * from the targeted server.
 */
int create_serversock(int port);

/**
 * delete_serversock - Dispose the server socket
 * @sock: The socket that is getting deleted.
 */
int delete_serversock(int sock);

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
int listen_serversock(int serversock, int max_clients, char *client_ip);

/**
 * create_sock - Create a socket connection
 * @ip_address: The server's ip-address
 * @port: The port of the socket
 * 
 * Returns the socket integer that you need as
 * a parameter to send and/or receive data
 * from the targeted server.
 */
int create_sock(char* ip_address, int port);

/**
 * delete_sock - Removes the socket connection
 * @sock - Socket to delete
 */
void delete_sock(int sock);

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
 * @buf_len - Length of the buffer
 *
 * Returns 0 on succes or -1 on error
 */
int receive_data(int sock, char* buf, int buf_len);

#endif
