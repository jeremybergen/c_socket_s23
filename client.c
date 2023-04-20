/*
c socket client
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int clientSocket;
    struct sockaddr_in address;
    // char buffer[1024] = {0};
    char *buffer;
    size_t bufferLen = 0;
    int connectStatus;
    
    address.sin_family = AF_INET;

    address.sin_port = htons(1234);
    inet_pton(AF_INET, "127.0.0.1", &(address.sin_addr));
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    connectStatus = connect(clientSocket, (struct sockaddr *)&address, sizeof(address));
    printf("Connection status is: %d\n", connectStatus);
    if(connectStatus == -1) {
        fprintf(stderr, "Error on connect --> %s\n", strerror(errno));
    }

    // strcat(buffer, "Hello\n");
    
    // buffer = readline("What do you want to send to the server? ");


    // while(1) {
        // printf("DEBUG: creating sendBuffer that we aren't using\n");
        // char sendBuffer[1024] = {0};
        // printf("DEBUG: memset buffer");
        memset(buffer, 0, sizeof(buffer));

        // printf("What mode do you want to go in? ");
        // getline(&buffer, &bufferLen, stdin);
        // // send(clientSocket, buffer, bufferLen, 0);

        // strcat(sendBuffer, buffer);
        // memset(buffer, 0, bufferLen);

        // printf("What do you want to send to the server? ");
        // getline(&buffer, &bufferLen, stdin);
        // strcat(sendBuffer, buffer);

        // send(clientSocket, sendBuffer, strlen(sendBuffer), 0);
        // printf("DEBUG: before first recv\n");
        recv(clientSocket, buffer, 1024, 0);
        printf("Received from server: %s\n", buffer);

        ssize_t fileSize = atol(buffer);
        ssize_t remainingBytes = fileSize;
        memset(buffer, 0, strlen(buffer));

        sprintf(buffer, "Received file size");
        send(clientSocket, buffer, strlen(buffer), 0);
        memset(buffer, 0, strlen(buffer));

        int fileDescriptor = open("outputFile", O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
        // printf("fileDescriptor: %d\n", fileDescriptor);
        while(remainingBytes > 0) {
            ssize_t recvBytes = recv(clientSocket, buffer, 1024, 0);
            // printf("DEBUG: strlen(buffer): %ld\n", strlen(buffer));
            ssize_t writeBytes = write(fileDescriptor, buffer, recvBytes);
            if (writeBytes != recvBytes) {
                printf("writeBytes: %ld\nrecvBytes: %ld\n", writeBytes, recvBytes);
            }

            remainingBytes -= recvBytes;
            printf("DEBUG: recvBytes: %ld\n", recvBytes);
            memset(buffer, 0, recvBytes);
        }

        printf("Closing fileDescriptor\n");
        close(fileDescriptor);

        // memset(buffer, 0, bufferLen);
    // }

    return 0;
}