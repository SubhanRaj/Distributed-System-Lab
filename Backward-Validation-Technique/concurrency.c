#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Data structure to represent a database entry
typedef struct
{
    int data;
    int version;
} DataEntry;
// Global data array
DataEntry data[2];
// Function to simulate forward validation
bool forwardValidation(int transaction, int readVersion, int writeVersion)
{
    if (readVersion < data[transaction].version)
    {
        printf("Transaction T%d failed forward validation.\n", transaction + 1);
        return false;
    }
    else
    {
        printf("Transaction T%d passed forward validation.\n", transaction + 1);
        data[transaction].version = writeVersion;
        return true;
    }
}
// Function to simulate backward validation
bool backwardValidation(int transaction, int readVersion, int writeVersion)
{
    if (readVersion < data[transaction].version)
    {
        printf("Transaction T%d failed backward validation.\n", transaction + 1);
        return false;
    }
    else
    {
        printf("Transaction T%d passed backward validation.\n", transaction + 1);
        data[transaction].version = writeVersion;
        return true;
    }
}
// Function to simulate a transaction
void executeTransaction(int transaction, int newData, int writeVersion)
{
    int readVersion = data[transaction].version;
    // Simulate forward validation
    if (forwardValidation(transaction, readVersion, writeVersion))
    {
        // Simulate transaction execution
        printf("Executing Transaction T%d...\n", transaction + 1);
        data[transaction].data = newData;
        printf("Transaction T%d completed.\n", transaction + 1);
    }
    else
    {
        printf("Transaction T%d aborted due to validation failure.\n", transaction + 1);
    }
}
int main()
{
    // Initialize data
    data[0].data = 10;
    data[0].version = 1;
    data[1].data = 20;
    data[1].version = 1;
    // Simulate transactions
    executeTransaction(0, 15, 2); // T1 with new data 15 and version 2
    executeTransaction(1, 25, 3); // T2 with new data 25 and version 3
    executeTransaction(0, 18, 4); // T1 with new data 18 and version 4
    executeTransaction(1, 30, 5); // T2 with new data 30 and version 5
    return 0;
}