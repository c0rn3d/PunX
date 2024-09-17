#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8096
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server;
    char message[BUFFER_SIZE], server_reply[BUFFER_SIZE];

    // Banner for the client starting up
    printf(">>> Booting up PunX Client [PORT: %d] <<<\n", PORT);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("[-] Could not create cyber-socket.\n");
        return 1;
    }
    printf("[+] Cyber-socket initialized.\n");

    // Set up server connection details
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "192.168.1.21", &server.sin_addr);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("[-] Connection failed");
        return 1;
    }
    printf("[+] Connected to PunX Server.\n");

    // Communication loop
    while (1) {
        printf(">>> Enter your [cyber] message: ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0';  // Remove newline

        // Send message to server
        if (send(sock, message, strlen(message), 0) < 0) {
            printf("[-] Send failed.\n");
            return 1;
        }

        // Clear server reply buffer
        memset(server_reply, 0, BUFFER_SIZE);

        // Receive server's reply
        int reply_len = recv(sock, server_reply, BUFFER_SIZE - 1, 0);
        if (reply_len < 0) {
            printf("[-] Receive failed.\n");
            break;
        }

        // Null-terminate server reply
        server_reply[reply_len] = '\0';

        // Display server reply
        printf("[Server] Echoing back: %s\n", server_reply);

        // Optional: Add a delay for that "cyberpunk lag" feel
        usleep(500000);  // 0.5-second delay
    }

    // Close socket after the loop ends
    close(sock);
    return 0;
}
