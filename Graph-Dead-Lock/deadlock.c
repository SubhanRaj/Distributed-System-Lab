#include <stdio.h>
#include <stdlib.h>
#define MAX_PROCESSES 100
// Function to perform DFS
int isCyclicUtil(int graph[MAX_PROCESSES][MAX_PROCESSES], int process, int visited[MAX_PROCESSES], int recursionStack[MAX_PROCESSES], int numProcesses)
{
    if (!visited[process])
    {
        visited[process] = 1;
        recursionStack[process] = 1;
        for (int i = 0; i < numProcesses; i++)
        {
            if (graph[process][i])
            {
                if (!visited[i] && isCyclicUtil(graph, i, visited, recursionStack, numProcesses))
                {
                    return 1;
                }
                else if (recursionStack[i])
                {
                    return 1;
                }
            }
        }
    }
    recursionStack[process] = 0;
    return 0;
}
// Function to check for deadlock using DFS
int isDeadlock(int graph[MAX_PROCESSES][MAX_PROCESSES], int numProcesses)
{
    int visited[MAX_PROCESSES] = {0};
    int recursionStack[MAX_PROCESSES] = {0};
    for (int i = 0; i < numProcesses; i++)
    {
        if (isCyclicUtil(graph, i, visited, recursionStack, numProcesses))
        {
            return 1; // Deadlock detected
        }
    }
    return 0; // No deadlock
}
int main()
{
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    int graph[MAX_PROCESSES][MAX_PROCESSES];
    printf("Enter the wait-for graph adjacency matrix (1 for edge, 0 for no edge):\n");
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numProcesses; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
    if (isDeadlock(graph, numProcesses))
    {
        printf("Deadlock detected!\n");
    }
    else
    {
        printf("No deadlock.\n");
    }
    return 0;
}