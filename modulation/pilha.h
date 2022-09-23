#ifndef QUEUE_DEF

#define QUEUE_DEF

#include <stdlib.h>

typedef struct{
    int value;
}Register;

typedef struct node{
    Register data;
    struct node *next;
}Node;

typedef struct queue{
    Node *top;
    void (*push)(struct queue *queue, int data);
    Register (*pop)(Node *top);
    void (*free)(struct queue *queue);
    void (*list)(Node *top);
}Queue;

Queue *queueInit();

#endif /*QUEUE_DEF*/