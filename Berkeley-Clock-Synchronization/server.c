#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 12345
#define MAX_CLIENTS 5
int main()
{
    int serverSocket, clientSockets[MAX_CLIENTS];
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
    if (listen(serverSocket, MAX_CLIENTS) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }
    printf("Server waiting for incoming connections...\n");
    // Accept connections from clients
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        clientSockets[i] = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSockets[i] == -1)
        {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }
        printf("Client %d connected\n", i + 1);
        // Get time from the client
        time_t clientTime;
        recv(clientSockets[i], &clientTime, sizeof(clientTime), 0);
        // Calculate time difference
        time_t serverTime;
        time(&serverTime);
        time_t timeDifference = serverTime - clientTime;
        // Send time difference to the client
        send(clientSockets[i], &timeDifference, sizeof(timeDifference), 0);
        // Close the socket for this client
        close(clientSockets[i]);
    }
    // Close the server socket
    close(serverSocket);
    return 0;
}