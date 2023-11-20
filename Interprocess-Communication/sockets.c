// Sockets provide communication between processes over a network. For interprocess //communication on the same machine, Unix domain sockets are commonly used.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
int main()
{
    int server_socket, client_socket;
    socklen_t server_len, client_len;
    struct sockaddr_un server_address, client_address;
    // Create a socket
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    // Set up the server address
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "ipc_socket");
    server_len = sizeof(server_address);
    // Bind the socket to a name
    bind(server_socket, (struct sockaddr *)&server_address, server_len);
    // Listen for connections
    listen(server_socket, 5);
    // Accept a connection
    printf("Server waiting for a connection...\n");
    client_len = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len);
    printf("Server accepted a connection.\n");
    // Communicate with the client (send and receive data)
    // Close sockets
    close(client_socket);
    close(server_socket);
    // Remove the socket file
    unlink("ipc_socket");
    return 0;
}