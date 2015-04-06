#ifdef __unix__
	#include <unistd.h>

	#define OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
	#include <winsock2.h>

	#define OS_WINDOWS
#endif

#include "debug.h"

/**
 * close_sock - Removes the socket connection
 * @sock - Socket to delete
 *
 * Returns 0 on succes or -1 on failure
 */
int close_sock(int sock)
{
#ifdef OS_WINDOWS
	closesocket(sock);
 	WSACleanup();
#endif
#ifdef OS_UNIX
	if (close(sock) < 0) {
        FEATHER_DBG_PRINT("ERROR: An error occured while closing a socket\n");
        return -1;
    }
#endif
    return 0;
}
