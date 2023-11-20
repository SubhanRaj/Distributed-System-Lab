#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
// Remote Object definition
typedef struct
{
    int value1;
    int value2;
} RemoteObject;
int add(int a, int b)
{
    return a + b;
}
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
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Error connecting to server");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");
    // Receive the remote object from the server
    RemoteObject remoteObject;
    recv(client_socket, &remoteObject, sizeof(RemoteObject), 0);
    // Invoke the remote method
    int result = add(remoteObject.value1, remoteObject.value2);
    printf("Result of remote method invocation: %d\n", result);
    // Close the socket
    close(client_socket);
    return 0;
}