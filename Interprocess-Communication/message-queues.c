// Message queues allow processes to communicate by passing messages.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message
{
    long msg_type;
    char msg_text[100];
};
int main()
{
    key_t key;
    int msgid;
    // Generate a unique key
    key = ftok("msgq_example", 'A');
    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    struct message msg;
    // Send a message
    msg.msg_type = 1;
    sprintf(msg.msg_text, "Hello from message queue");
    msgsnd(msgid, &msg, sizeof(msg), 0);
    // Receive a message
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    printf("Received message: %s\n", msg.msg_text);
    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}