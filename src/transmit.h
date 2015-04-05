#ifndef TRANSMIT_H
#define TRANSMIT_H
    /* see headers/feathernet.h for usage */
    int send_data(int sock, char* msg);

    /* see headers/feathernet.h for usage */
    int receive_data(int sock, char* buf, int buf_len);
#endif
