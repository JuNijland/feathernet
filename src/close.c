#ifdef __unix__
	#include <unistd.h>

	#define OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
	#include <winsock2.h>

	#define OS_WINDOWS
#endif

/**
 * delete_sock - Removes the socket connection
 * @sock - Socket to delete
 */
int close_sock(int sock)
{
#ifdef OS_WINDOWS
	closesocket(sock);
 	WSACleanup();
#endif
#ifdef OS_UNIX
	if (close(sock) < 0) {
#ifdef FEATHER_DEBUG
        printf("ERROR: An error occured while closing a socket\n");
#endif
        return -1;
    }
#endif
    return 0;
}
