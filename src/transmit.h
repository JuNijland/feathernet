#ifndef TRANSMIT_H
#define TRANSMIT_H
    int send_data(int sock, char* msg);
    int receive_data(int sock, char* buf, int buf_len);
#endif
