#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    // Set up server address struct
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }
    // Listen for incoming connections
    if (listen(server_socket, 5) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    // Accept connection from client
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len)) == -1)
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    // Communication with client
    char buffer[BUFFER_SIZE];
    int bytes_received;
    while (1)
    {
        // Receive data from client
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0)
        {
            perror("Error receiving data");
            break;
        }
        buffer[bytes_received] = '\0'; // Null-terminate the received data
        // Print received data
        printf("Received from client: %s\n", buffer);
        // Send a response to the client
        send(client_socket, buffer, strlen(buffer), 0);
    }
    // Close sockets
    close(client_socket);
    close(server_socket);
    return 0;
}