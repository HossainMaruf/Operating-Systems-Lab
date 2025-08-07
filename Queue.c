#include <stdio.h>
#include <stdbool.h>
#define QUEUE_SIZE 10

typedef struct {
    int pid, at, bt, wt, st, ct, tt;
} Process;

int front = -1, rear = -1;
Process* readyQueue[QUEUE_SIZE];
int isEmpty(void) { return (front == -1) && (rear == -1); }
int size(void) { return rear+1; }
void enqueue(Process *p) {
    if(isEmpty) {
        // push first time
        readyQueue[++rear] = p; // now rear is 0
        front = 0; // front is also 0
    } else {
        // TODO: check for full or not
        readyQueue[++rear] = p;
    }
}

Process* dequeue(void) {
    if(isEmpty()) return NULL;
    else if(front == 0 && rear == 0) {
        front = -1;
        return readyQueue[rear--];
    } else return readyQueue[rear--];
}

void os(Process process[], int n) { 
    // based on arrial time os push the process to the readyQueue
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-1-i; j++) {
            if(process[j].at > process[j+1].at) {
                Process temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }
    for(int i=0; i<n; i++) {
        enqueue(&process[i]);
    }
}

void printReadyQueue() {
    printf("PID\tAT\tBT\tWT\tST\tCT\tTT\n");
    printf("--------------------------------------------------\n");
    for(int i=0; i<size(); i++) {
        printf("P%d\t%d\t%d\n", (*readyQueue[i]).pid, (*readyQueue[i]).at, (*readyQueue[i]).bt);
    }
    printf("\n");
}


void main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    Process process[n];
    for(int i=0; i<n; i++) {
        process[i].pid = i+1;
        scanf("%d%d", &process[i].at, &process[i].bt);
    }
    os(process, n);
    printReadyQueue();
}