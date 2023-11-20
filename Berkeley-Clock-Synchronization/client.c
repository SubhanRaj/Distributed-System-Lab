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
    // Get current client time
    time_t clientTime;
    time(&clientTime);
    // Send client time to the server
    send(clientSocket, &clientTime, sizeof(clientTime), 0);
    // Receive time difference from the server
    time_t timeDifference;
    recv(clientSocket, &timeDifference, sizeof(timeDifference), 0);
    // Adjust client clock
    time_t adjustedTime = clientTime + timeDifference;
    printf("Client Time: %s", ctime(&clientTime));
    printf("Time Difference: %ld seconds\n", timeDifference);
    printf("Adjusted Client Time: %s", ctime(&adjustedTime));
    // Close socket
    close(clientSocket);
    return 0;
}