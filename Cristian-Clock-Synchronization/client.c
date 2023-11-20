#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 12345
int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    // Set up server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
    // Receive server time
    time_t serverTime;
    recv(clientSocket, &serverTime, sizeof(serverTime), 0);
    // Record local receive time
    time_t localReceiveTime;
    time(&localReceiveTime);
    // Calculate round-trip time
    double roundTripTime = difftime(localReceiveTime, serverTime);
    // Adjust client clock
    time_t adjustedTime = serverTime + (time_t)(roundTripTime / 2.0);
    printf("Server Time: %s", ctime(&serverTime));
    printf("Round-trip Time: %.2lf seconds\n", roundTripTime);
    printf("Adjusted Client Time: %s", ctime(&adjustedTime));
    // Close socket
    close(clientSocket);
    return 0;
}