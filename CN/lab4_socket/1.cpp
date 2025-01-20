#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sockfd1, sockfd2;

    sockfd1 = socket(AF_INET, SOCK_STREAM, 0); 
    sockfd2 = socket(PF_INET, SOCK_DGRAM, 0);

    if (sockfd1 == -1) {
        printf("Socket1 not Created\n");
    } else {
        printf("Socket1 Created and \nSocket1 File Descriptor value is %d \n", sockfd1);

        if (sockfd2 == -1) {
            printf("socket2 creation error\n");
        } else {
            printf("Socket2 created and \nSocket2 descriptor value is %d\n", sockfd2);
        }
    }

    return 0;
}
