#include <stdio.h>
#include "queue.h"

void initializeQueue(Queue *q) { q->front = -1, q->rear = -1; }
int isEmpty(Queue *q) { return ((q->front) == -1) && ((q->rear) == -1); }
int size(Queue *q) { return (q->rear)+1; }
int isFull(Queue *q) { return (size(q) == QUEUE_SIZE) ? 1 : 0; }

Type enqueue(Queue *q, Type item) {
    if(isFull(q)) return NULL; // no space for enqueue
    if(isEmpty(q)) (q->front) = 0; // first time push so front should be 0
    return q->data[++(q->rear)] = item;  // enqueue the item and return it
}

Type dequeue(Queue *q) {
    if (isEmpty(q)) return NULL;
    else {
        // so take the (q->front) in temp
        Type temp = q->data[q->front];
        // Shift left all the elements by 1 index 
        for(int i=(q->front); i< (q->rear); i++) q->data[i] = q->data[i+1];
        (q->rear)--; // decrease the rear value
        if((q->rear) == -1) (q->front) = -1;
        return temp;
    }
}

Type first(Queue *q) { return isEmpty(q) ? NULL : q->data[q->front]; }