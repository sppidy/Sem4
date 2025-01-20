#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BACKLOG 2
#define PORT 3490

int main() {
    int fd, fd2;
    struct sockaddr_in server;
    socklen_t sin_size;
    struct sockaddr_in client;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("socket() error\n");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero), 8);

    if (bind(fd, (struct sockaddr*)&server, sizeof(struct sockaddr)) == -1) {
        printf("bind() error\n");
        exit(-1);
    }

    if (listen(fd, BACKLOG) == -1) {
        printf("listen() error\n");
        exit(-1);
    }

    printf("server is in accept mode\n");

    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((fd2 = accept(fd, (struct sockaddr*)&client, &sin_size)) == -1) {
            printf("accept() error\n");
            exit(-1);
        } else {
            printf("Server is in accept mode\n");
            printf("You got a connection from %s\n", inet_ntoa(client.sin_addr));
            close(fd2);
        }
    }
}
