#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 12345

const char* get_ip_class(struct in_addr ip) {
    unsigned int ip_int = ntohl(ip.s_addr);

    if (ip_int >= 0x00000000 && ip_int <= 0x7F000000) {
        return "Class A";
    } else if (ip_int >= 0x80000000 && ip_int <= 0xBFFFFFFF) {
        return "Class B";
    } else if (ip_int >= 0xC0000000 && ip_int <= 0xDFFFFFFF) {
        return "Class C";
    } else if (ip_int >= 0xE0000000 && ip_int <= 0xEFFFFFFF) {
        return "Class D (Multicast)";
    } else {
        return "Class E (Reserved)";
    }
}

int get_num_hosts(int prefix_len) {
    if (prefix_len < 0 || prefix_len > 32) {
        return -1;
    }
    return (1 << (32 - prefix_len)) - 2;
}

void calculate_start_end_ip(struct in_addr ip, unsigned int subnet_mask, struct in_addr *start_ip, struct in_addr *end_ip) {
    unsigned int ip_int = ntohl(ip.s_addr);
    unsigned int mask_int = (0xFFFFFFFF << (32 - subnet_mask)) & 0xFFFFFFFF;

    unsigned int network_address = ip_int & mask_int;  // Network address (starting IP)
    unsigned int broadcast_address = network_address | (~mask_int);  // Broadcast address (ending IP)

    start_ip->s_addr = htonl(network_address);
    end_ip->s_addr = htonl(broadcast_address);
}

void process_ip(char *input, char *response) {
    struct in_addr ip, start_ip, end_ip;
    unsigned int subnet_mask;
    char ip_str[INET_ADDRSTRLEN];
    char start_ip_str[INET_ADDRSTRLEN], end_ip_str[INET_ADDRSTRLEN];
    int num_hosts;

    printf("Debug - Received from client: %s\n", input);

    // Split the input string using strtok() to separate IP and subnet mask
    char *ip_part = strtok(input, "/");
    char *subnet_part = strtok(NULL, "/");

    if (ip_part == NULL) {
        strcpy(response, "Invalid format for IP");
        return;
    }

    strcpy(ip_str, ip_part);

    if (subnet_part != NULL) {  // CIDR notation exists
        subnet_mask = atoi(subnet_part);

        if (inet_pton(AF_INET, ip_str, &ip) <= 0) {
            strcpy(response, "Invalid IP Address");
            return;
        }

        const char* ip_class = get_ip_class(ip);
        num_hosts = get_num_hosts(subnet_mask);
        if (num_hosts == -1) {
            strcpy(response, "Invalid CIDR prefix length");
            return;
        }

        // Calculate starting and ending IP
        calculate_start_end_ip(ip, subnet_mask, &start_ip, &end_ip);

        // Convert the starting and ending IP to string
        inet_ntop(AF_INET, &start_ip, start_ip_str, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &end_ip, end_ip_str, INET_ADDRSTRLEN);

        // Format the response for classless (CIDR)
        sprintf(response, "Number of Hosts: %d\nStarting IP: %s\nEnding IP: %s\n",
                num_hosts, start_ip_str, end_ip_str);

    } else {  // Classful address (no CIDR notation)
        if (inet_pton(AF_INET, ip_str, &ip) <= 0) {
            strcpy(response, "Invalid IP Address");
            return;
        }

        const char* ip_class = get_ip_class(ip);
        sprintf(response, "IP Class: %s\n", ip_class);
    }
}

void start_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char response[1024];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;  // Keep the server running even if accept fails
        }

        int bytes_read = read(new_socket, buffer, sizeof(buffer)-1);
        if (bytes_read <= 0) {
            perror("Read failed");
            close(new_socket);
            continue;  // Continue the loop to accept the next connection
        }

        buffer[bytes_read] = '\0';
        printf("Debug - Received from client: %s\n", buffer);

        process_ip(buffer, response);
        printf("Response: %s\n", response);

        send(new_socket, response, strlen(response), 0);
        printf("Response sent to client\n");

        close(new_socket);
    }

    close(server_fd);
}

int main() {
    start_server();
    return 0;
}

