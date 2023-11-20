// Semaphores are used for synchronization between processes.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
int main()
{
    key_t key;
    int semid;
    struct sembuf sem_op;
    // Generate a unique key
    key = ftok("sem_example", 'A');
    // Create a semaphore set
    semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("Error creating semaphore");
        exit(EXIT_FAILURE);
    }
    // Initialize the semaphore
    semctl(semid, 0, SETVAL, 1);
    printf("Semaphore initialized to 1\n");
    // Perform semaphore operations (wait and signal)
    sem_op.sem_num = 0;
    sem_op.sem_op = -1; // Wait
    sem_op.sem_flg = 0;
    printf("Attempting to enter the critical section...\n");
    semop(semid, &sem_op, 1); // Wait
    printf("Entered the critical section\n");
    // Critical section (protected by semaphore)
    // Simulate some processing time within the critical section
    sleep(2);
    printf("Exiting the critical section\n");
    sem_op.sem_op = 1;        // Signal
    semop(semid, &sem_op, 1); // Signal
    printf("Semaphore value incremented. Exiting the program.\n");
    // Remove the semaphore set
    if (semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("Error removing semaphore");
        exit(EXIT_FAILURE);
    }
    return 0;
}