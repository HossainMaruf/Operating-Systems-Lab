#include <stdio.h>
#include <stdbool.h>
#include "vector.h"
Vector v;

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
            push_back(&v, &process[i]);
        }
    }
    time++; // time goes
}

void cpu(Process *p) {

}

Process* NonPreemptive_SJF(Vector *v) {
    // sort according to BT
    int n = size(&v);
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-1-i; j++) {
            Process *left = v->data[j];
            Process *right = v->data[j+1];
            if(left->bt > right->bt) {
                Process *temp = left;
                *left = *right;
                *right = *temp;
            }
        }
    }
    // execute all the sorted process
    
}

Process* scheduler() {
    if(size(&v) == 1) return v.data[0];
    else NonPreemptive_SJF(&v);
}


void printReadyQueue() {
    printf("PID\tAT\tBT\tWT\tST\tCT\tTT\n");
    printf("--------------------------------------------------\n");
    for(int i=0; i<size(&v); i++) {
        Process *p = v.data[i];
        printf("P%d\t%d\t%d\n", p->pid, p->at, p->bt);
    }
    printf("\n");
}


int main() {
    initializeVector(&v);
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    Process process[n];
    for(int i=0; i<n; i++) {
        process[i].pid = i+1;
        scanf("%d%d", &process[i].at, &process[i].bt);
    }
    sort(process, n); // sort processes by arrival time 
    os(process, n); // using arrival time push to the ready queue
    printReadyQueue(); // print the status of ready queue 
    scheduler(); // which one need to be scheduled next
    freeVector(&v);
    return 0;
}