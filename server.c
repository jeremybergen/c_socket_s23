/*
C Socket Server
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>

// int main(int argc, char *argv[]) {
int main(int argc, char **argv) {
    // printf("Hello World\n");
    int serverSocket;
    int clientSocket;
    int yes = 1;
    struct sockaddr_in address;
    int addrsize = sizeof(struct sockaddr_storage);
    // int serverSocket2;

    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(1234);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Our socket number is: %d\n", serverSocket);

    // serverSocket2 = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    bind(serverSocket, (struct sockaddr *)&address, sizeof(address));
    listen(serverSocket, 1);

    clientSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t *)&addrsize);
    printf("Accepted new connection on socket number: %d\n", clientSocket);

    while(1) {

    }
    return 0;
}