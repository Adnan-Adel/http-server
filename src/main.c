#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "../include/request_handler.h"


#define PORT_NUM            2020
#define REQUEST_SIZE        1024
#define BACKLOG             5

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;
    char request[REQUEST_SIZE];

    /* make server socket */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    /* construct server address */
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_NUM);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* bind socket to address */
    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    /* listen for connections */
    if(listen(server_socket, BACKLOG) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    /* handle client connections */
    len = sizeof(struct sockaddr_in);
    for(;;) {
        /* accept client connection */
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len);
        if(client_socket == -1) {
            perror("client socket creation failed");
            exit(EXIT_FAILURE);
        }

        /* server recieves a request from client */
        int bytes_received = recv(client_socket, request, REQUEST_SIZE, 0);
        request[bytes_received] = '\0';

        /* server handles request */
        handle_request(request, client_socket);
    }

    return 0;
}
