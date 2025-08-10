#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 50

typedef void* Type;
typedef struct {
    int front, rear;
    Type data[QUEUE_SIZE];
} Queue;

extern void initializeQueue(Queue*);
extern int isEmpty(Queue*);
extern int size(Queue*);
extern int isFull(Queue*);
extern Type enqueue(Queue*, Type);
extern Type dequeue(Queue*);
extern Type first(Queue*);

#endif