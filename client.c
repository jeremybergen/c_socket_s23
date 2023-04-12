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

int main(int argc, char **argv) {
    int clientSocket;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    connect(clientSocket, (struct sockaddr *)&address, sizeof(address));

    strcat(buffer, "Hello\n");
    send(clientSocket, buffer, 6, 0);
    recv(clientSocket, buffer, 1024, 0);
    printf("Received from server: %s\n", buffer);

    return 0;
}