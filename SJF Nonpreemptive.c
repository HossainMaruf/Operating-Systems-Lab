#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
Queue q;

int time = 0;
typedef struct {
    int pid, at, bt, wt, st, ct, tt;
} Process;

void sort(Process process[], int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-1-i; j++) {
            if(process[j].at > process[j+1].at) {
                Process temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }
}

void os(Process process[], int n) { 
    for(int i=0; i<n; i++) { // scanning total array but we should not do that
        if(process[i].at == time) {
            enqueue(&q, &process[i]);
        }
    }
    time++; // time goes
}

void cpu(Process *p) {

}

void scheduler() {
    if(size(&q) == 1) {
        // only one process so scheduled it
        return pop(&q);
    } else {
        // more than one process so apply algorithm
        return NonPreemptive_SJF(&q);
    }
}

void dispatcher() {

}

void printReadyQueue() {
    printf("PID\tAT\tBT\tWT\tST\tCT\tTT\n");
    printf("--------------------------------------------------\n");
    while(!isEmpty(&q)) {
        Process *p = dequeue(&q);
        printf("P%d\t%d\t%d\n", p->pid, p->at, p->bt);
    }
    printf("\n");
}


void main() {
    initializeQueue(&q);
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    Process process[n];
    for(int i=0; i<n; i++) {
        process[i].pid = i+1;
        scanf("%d%d", &process[i].at, &process[i].bt);
    }
    sort(process, n); // sort processes by arrival time 
    os(process, n); // using arrival time push to the readyQueue
//    printReadyQueue(); // print the status of readyQueue
   scheduler(); // which one need to be scheduled next
//    dispatcher(); // calculate the things
}