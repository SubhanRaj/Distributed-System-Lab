#include <stdio.h>
#include <stdlib.h>
#define NUM_PROCESSES 3
typedef struct
{
    int process_id;
    int vector_clock[NUM_PROCESSES];
} Event;
void updateVectorClock(int *vector_clock, int process_id, int new_timestamp)
{
    vector_clock[process_id] = new_timestamp + 1;
}
void simulateMatternFidgeVectorClocks()
{
    int vector_clock_A[NUM_PROCESSES] = {0};
    int vector_clock_B[NUM_PROCESSES] = {0};
    int vector_clock_C[NUM_PROCESSES] = {0};
    // Event for Process A
    Event event_A1 = {0, {0}};
    printf("Event A1 - Process %d, Vector Clock: [%d, %d, %d]\n",
           event_A1.process_id, event_A1.vector_clock[0], event_A1.vector_clock[1], event_A1.vector_clock[2]);
    // Update vector clock for Process A
    updateVectorClock(vector_clock_A, event_A1.process_id, event_A1.vector_clock[0]);
    // Event for Process B
    Event event_B1 = {1, {0}};
    printf("Event B1 - Process %d, Vector Clock: [%d, %d, %d]\n",
           event_B1.process_id, event_B1.vector_clock[0], event_B1.vector_clock[1], event_B1.vector_clock[2]);
    // Update vector clock for Process B
    updateVectorClock(vector_clock_B, event_B1.process_id, event_B1.vector_clock[1]);
    // Event for Process C
    Event event_C1 = {2, {0}};
    printf("Event C1 - Process %d, Vector Clock: [%d, %d, %d]\n",
           event_C1.process_id, event_C1.vector_clock[0], event_C1.vector_clock[1], event_C1.vector_clock[2]);
    // Update vector clock for Process C
    updateVectorClock(vector_clock_C, event_C1.process_id, event_C1.vector_clock[2]);
    // Event for Process A
    Event event_A2 = {0, {0}};
    printf("Event A2 - Process %d, Vector Clock: [%d, %d, %d]\n",
           event_A2.process_id, event_A2.vector_clock[0], event_A2.vector_clock[1], event_A2.vector_clock[2]);
    // Update vector clock for Process A
    updateVectorClock(vector_clock_A, event_A2.process_id, event_A2.vector_clock[0]);
    // Event for Process B
    Event event_B2 = {1, {0}};
    printf("Event B2 - Process %d, Vector Clock: [%d, %d, %d]\n",
           event_B2.process_id, event_B2.vector_clock[0], event_B2.vector_clock[1], event_B2.vector_clock[2]);
    // Update vector clock for Process B
    updateVectorClock(vector_clock_B, event_B2.process_id, event_B2.vector_clock[1]);
    // Event for Process C
    Event event_C2 = {2, {0}};
    printf("Event C2 - Process %d, Vector Clock: [%d, %d, %d]\n",
           event_C2.process_id, event_C2.vector_clock[0], event_C2.vector_clock[1], event_C2.vector_clock[2]);
    // Update vector clock for Process C
    updateVectorClock(vector_clock_C, event_C2.process_id, event_C2.vector_clock[2]);
}
int main()
{
    simulateMatternFidgeVectorClocks();
    return 0;
}