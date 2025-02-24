#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

void start_client(const char *server_ip) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[1024];
    char buffer[1024];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return;
    }

    // Prompt for IP address with CIDR (e.g., 192.168.0.0/24)
    printf("Enter IP address with CIDR (e.g., 192.168.0.0/8): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;  // Remove the newline character

    // Debugging: Print the message before sending
    // printf("Debug - Sending to server: %s\n", message);

    // Send the message to the server
    send(sock, message, strlen(message), 0);

    // Read the server response
    int bytes_read = read(sock, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        perror("Read failed");
        close(sock);
        return;
    }

    buffer[bytes_read] = '\0';  // Null-terminate the buffer
    printf("Server Response:\n%s\n", buffer);

    close(sock);
}

int main() {
    const char *server_ip = "127.0.0.1";  // Change this to your server's IP if needed
    start_client(server_ip);
    return 0;
}

