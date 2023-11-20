#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 12345
int main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    // Set up server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    // Bind socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }
    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }
    printf("Server waiting for incoming connections...\n");
    // Accept connection from client
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
    if (clientSocket == -1)
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }
    // Get current server time
    time_t serverTime;
    time(&serverTime);
    // Send server time to the client
    send(clientSocket, &serverTime, sizeof(serverTime), 0);
    // Close sockets
    close(clientSocket);
    close(serverSocket);
    return 0;
}