#include "../include/request_handler.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "../include/error.h"


void handle_request(char *request, int client_socket) {
    char method[8], file_path[256];
    sscanf(request, "%s %s", method, file_path);

    if(strcmp(method, "GET") != 0) {
        send_405(client_socket);
        return;
    }

    // Map "/" to "index.html"
    if(strcmp(file_path, "/") == 0) {
        strcpy(file_path, "index.html");
    }
    else {
        // remove leading '/'
        memmove(file_path, file_path + 1, strlen(file_path));
    }


    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        send_404(client_socket);
        return;
    }

    char response_data[4096] = "";
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        strcat(response_data, buffer);
    }
    fclose(file);

    // build HTTP response
    char http_header[8192];
    snprintf(http_header, sizeof(http_header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "Content-Length: %ld\r\n"
             "\r\n"
             "%s",
             strlen(response_data), response_data);

    // send response
    send(client_socket, http_header, strlen(http_header), 0);
}
