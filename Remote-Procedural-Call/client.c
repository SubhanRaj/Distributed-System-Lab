#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
    int client_socket;
    struct sockaddr_in server_addr;
    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    // Set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Error connecting to server");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");
    // Send operation code to the server
    int operation = 1; // 1 for addition
    send(client_socket, &operation, sizeof(operation), 0);
    if (operation == 1)
    { // Addition
        // Send data to the server
        int a = 3, b = 4;
        send(client_socket, &a, sizeof(a), 0);
        send(client_socket, &b, sizeof(b), 0);
        // Receive the result from the server
        int result;
        recv(client_socket, &result, sizeof(result), 0);
        printf("Result received from server: %d\n", result);
    }
    // Close the socket
    close(client_socket);
    return 0;
}