#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
// Remote procedure: Addition
int add(int a, int b)
{
    return a + b;
}
int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    // Set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Error binding");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    // Listen for incoming connections
    if (listen(server_socket, 5) == -1)
    {
        perror("Error listening");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port 8888...\n");
    // Accept a connection from the client
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket == -1)
    {
        perror("Error accepting connection");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    // Receive data from the client
    int operation;
    recv(client_socket, &operation, sizeof(operation), 0);
    if (operation == 1)
    { // Addition
        int a, b, result;
        recv(client_socket, &a, sizeof(a), 0);
        recv(client_socket, &b, sizeof(b), 0);
        // Call the remote procedure
        result = add(a, b);
        // Send the result back to the client
        send(client_socket, &result, sizeof(result), 0);
    }
    // Close sockets
    close(client_socket);
    close(server_socket);
    return 0;
}