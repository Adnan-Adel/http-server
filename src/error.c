#include "../include/error.h"
#include <string.h>
#include <sys/socket.h>


void send_404(int socket){
    const char *not_found = "HTTP/1.1 404 Not Found\r\n\r\n<h1>404 Not Found</h1>";
    send(socket, not_found, strlen(not_found), 0);
}

void send_405(int socket) {
    const char *not_allowed = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
    send(socket, not_allowed, strlen(not_allowed), 0);
}
