#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define PORT 8096
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

void *handle_client(void *client_socket) {
    int sock = *((int *)client_socket);
    free(client_socket);
    char buffer[BUFFER_SIZE];
    int read_size;
    
    printf("\n[+] A new cyber-node connected.\n");

    while ((read_size = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        // Null-terminate the received data
        buffer[read_size] = '\0';
        
        printf("[+] Incoming message: %s\n", buffer);

        // Echo message back to client (can be encrypted for a more cyberpunk twist)
        send(sock, buffer, strlen(buffer), 0);

        // Optional: Add a cyberpunk delay effect
        printf("[+] Echoing back to the node...\n");
        usleep(500000);  // Small delay to simulate "cybernetic lag"
    }
    
    if (read_size == 0) {
        printf("[-] Connection terminated by the node.\n");
    } else if (read_size == -1) {
        perror("recv failed");
    }
    
    close(sock);
    return NULL;
}

int main() {
    int server_sock, client_sock, *new_sock;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    // Banner for the server starting up
    printf(">>> Initializing PunX Server [PORT: %d] <<<\n", PORT);
    
    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        printf("[-] Could not create cyber-socket.\n");
        return 1;
    }
    printf("[+] Cyber-socket initialized.\n");

    // Prepare sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("[-] Binding failed");
        return 1;
    }
    printf("[+] Socket bound. Cyberpunk node is ready.\n");

    // Listen for connections
    listen(server_sock, MAX_CLIENTS);
    printf("[+] Listening for connections on port %d...\n", PORT);

    // Accept incoming connections
    while ((client_sock = accept(server_sock, (struct sockaddr *)&client, &client_len))) {
        printf("[+] Incoming connection from a cyber-node.\n");

        new_sock = malloc(1);
        *new_sock = client_sock;

        if (pthread_create(&thread_id, NULL, handle_client, (void *)new_sock) < 0) {
            perror("[-] Failed to create thread");
            return 1;
        }

        printf("[+] Thread assigned. Handling the new node...\n");
    }

    if (client_sock < 0) {
        perror("[-] Accept failed");
        return 1;
    }

    return 0;
}
