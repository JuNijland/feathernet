#ifndef FEATHER_TRANSMIT_H
#define FEATHER_TRANSMIT_H
    /* see headers/feathernet.h for usage */
    int send_data(int sock, const char* msg);

    /* see headers/feathernet.h for usage */
    int receive_data(int sock, char* buf, int buf_len);
#endif
