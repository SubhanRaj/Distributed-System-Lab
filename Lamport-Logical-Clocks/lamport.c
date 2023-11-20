#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int process_id;
    int timestamp;
} Event;
void updateTimestamp(int *logical_clock, int new_timestamp)
{
    *logical_clock = (new_timestamp > *logical_clock) ? new_timestamp + 1 : *logical_clock + 1;
}
void simulateLamportClocks()
{
    int logical_clock_A = 0;
    int logical_clock_B = 0;
    // Event for Process A
    Event event_A1 = {1, logical_clock_A};
    printf("Event A1 - Process %d, Logical Clock: %d\n", event_A1.process_id, event_A1.timestamp);
    // Update logical clock for Process A
    updateTimestamp(&logical_clock_A, event_A1.timestamp);
    // Event for Process B
    Event event_B1 = {2, logical_clock_B};
    printf("Event B1 - Process %d, Logical Clock: %d\n", event_B1.process_id, event_B1.timestamp);
    // Update logical clock for Process B
    updateTimestamp(&logical_clock_B, event_B1.timestamp);
    // Event for Process A
    Event event_A2 = {1, logical_clock_A};
    printf("Event A2 - Process %d, Logical Clock: %d\n", event_A2.process_id, event_A2.timestamp);
    // Update logical clock for Process A
    updateTimestamp(&logical_clock_A, event_A2.timestamp);
    // Event for Process B
    Event event_B2 = {2, logical_clock_B};
    printf("Event B2 - Process %d, Logical Clock: %d\n", event_B2.process_id, event_B2.timestamp);
    // Update logical clock for Process B
    updateTimestamp(&logical_clock_B, event_B2.timestamp);
}
int main()
{
    simulateLamportClocks();
    return 0;
}