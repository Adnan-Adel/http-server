#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "../include/request_handler.h"


#define PORT_NUM            2020
#define REQUEST_SIZE        1024
#define BACKLOG             5

typedef struct {
    int client_socket;
    struct sockaddr_in client_addr;
} client_info_t;

void *handle_client_thread(void *arg) {
    client_info_t *info = (client_info_t *)arg;
    char request[REQUEST_SIZE];

    int bytes_received = recv(info->client_socket, request, REQUEST_SIZE - 1, 0);
    if (bytes_received <= 0) {
        perror("recv failed or client disconnected");
        close(info->client_socket);
        free(info);
        pthread_exit(NULL);
    }

    request[bytes_received] = '\0';

    // Handle the HTTP request
    handle_request(request, info->client_socket);

    close(info->client_socket);
    free(info);
    pthread_exit(NULL);
}



int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;
    // char request[REQUEST_SIZE];

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
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    /* listen for connections */
    if(listen(server_socket, BACKLOG) == -1) {
        perror("listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d...\n", PORT_NUM);

    /* handle client connections */
    for(;;) {
        len = sizeof(client_addr);
        /* accept client connection */
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len);
        if(client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        // Log client info
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        printf("[+] Client connected from %s:%d\n", client_ip, ntohs(client_addr.sin_port));


        // Allocate client info struct
        client_info_t *client = malloc(sizeof(client_info_t));
        client->client_socket = client_socket;
        client->client_addr = client_addr;

        // create a thread to handle client
        pthread_t tid;
        if(pthread_create(&tid, NULL, handle_client_thread, client) != 0) {
            perror("Failed to create thread");
            close(client_socket);
            free(client);
        }

        pthread_detach(tid);

        // /* server recieves a request from client */
        // int bytes_received = recv(client_socket, request, REQUEST_SIZE, 0);
        // request[bytes_received] = '\0';
        //
        // /* server handles request */
        // handle_request(request, client_socket);
    }

    return 0;
}
