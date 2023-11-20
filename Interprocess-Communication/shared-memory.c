// Shared memory allows processes to share a region of memory.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
    key_t key;
    int shmid;
    char *shared_memory;
    // Generate a unique key
    key = ftok("shm_example", 'A');
    // Create shared memory
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    // Attach shared memory
    shared_memory = shmat(shmid, NULL, 0);
    // Write to shared memory
    sprintf(shared_memory, "Hello from shared memory");
    // Detach shared memory
    shmdt(shared_memory);
    // Attach again to read from shared memory
    shared_memory = shmat(shmid, NULL, 0);
    printf("Shared memory contains: %s\n", shared_memory);
    // Detach shared memory
    shmdt(shared_memory);
    // Remove shared memory
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}