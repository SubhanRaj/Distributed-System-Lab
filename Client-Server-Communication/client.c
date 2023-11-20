#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main()
{
    int client_socket;
    struct sockaddr_in server_address;
    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    // Set up server address struct
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Connect to localhost
    server_address.sin_port = htons(PORT);
    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server on port %d\n", PORT);
    // Communication with server
    char buffer[BUFFER_SIZE];
    int bytes_received;
    while (1)
    {
        // Get user input
        printf("Enter message (type 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        // Send data to server
        send(client_socket, buffer, strlen(buffer), 0);
        if (strcmp(buffer, "exit\n") == 0)
        {
            break;
        }
        // Receive response from server
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0)
        {
            perror("Error receiving data");
            break;
        }
        buffer[bytes_received] = '\0'; // Null-terminate the received data
        // Print received data
        printf("Received from server: %s\n", buffer);
    }
    // Close socket
    close(client_socket);
    return 0;
}