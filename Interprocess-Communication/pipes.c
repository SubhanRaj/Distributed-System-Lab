// Pipes allow communication between two related processes.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int pipe_fd[2];
    char buffer[20];
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed");
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        return 1;
    }
    if (pid == 0)
    {
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipe_fd[0]);
    }
    else
    {
        close(pipe_fd[0]);
        write(pipe_fd[1], "Hello from parent", 17);
        close(pipe_fd[1]);
    }
    return 0;
}