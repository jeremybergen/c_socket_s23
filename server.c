/*
C Socket Server
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

// int main(int argc, char *argv[]) {
int main(int argc, char **argv) {
    int serverSocket;
    int clientSocket;
    struct addrinfo hints, *res;
    struct sockaddr_in address;
    int addrsize = sizeof(struct sockaddr_storage);
    int yes = 1;

    char buffer[1024] = {0};
    int readBytes = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "1234", &hints, &res);

    serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    bind(serverSocket, res->ai_addr, res->ai_addrlen);

    listen(serverSocket, 1);

    clientSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t *)&addrsize);
    while(1) {
        readBytes = recv(clientSocket, buffer, 1024, 0);
        printf("We received: %s\n", buffer);
        send(clientSocket, buffer, readBytes, 0);
        memset(buffer, 0, readBytes);
        
    }

    return 0;
}




    // // printf("Hello World\n");
    // int serverSocket;
    // int clientSocket;
    // int yes = 1;
    // struct sockaddr_in address;
    // int addrsize = sizeof(struct sockaddr_storage);
    // char buffer[1024] = {0};
    // // int serverSocket2;

    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_family = AF_INET;
    // address.sin_port = htons(1234);

    // serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // printf("Our socket number is: %d\n", serverSocket);

    // // serverSocket2 = socket(AF_INET, SOCK_STREAM, 0);
    // setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    // bind(serverSocket, (struct sockaddr *)&address, sizeof(address));
    // listen(serverSocket, 1);

    // clientSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t *)&addrsize);
    // printf("Accepted new connection on socket number: %d\n", clientSocket);

    // while(1) {
    //     recv(clientSocket, buffer, 1024, 0);
    //     printf("We received: %s\n", buffer);
    //     send(clientSocket, buffer, sizeof(buffer), 0);
    //     memset(buffer, 0, sizeof(buffer));
    // }