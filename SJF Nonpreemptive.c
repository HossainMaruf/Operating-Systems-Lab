/**
 * Problem 1: https://www.guru99.com/shortest-job-first-sjf-scheduling.html 
 * Problem 2: https://www.tutorialspoint.com/operating_system/os_shortest_job_first_scheduling.htm
 * Problem 3: https://www.gatevidyalay.com/sjf-scheduling-srtf-cpu-scheduling/
 */ 
#include <stdio.h>
#include <stdbool.h>
#include "vector.h"
Vector v;

int time = 0, total_wt = 0, total_tt = 0, processedCounter = 0;
typedef struct {
    int pid, at, bt, wt, st, ct, tt, status;
    /**
     * status = -1, The process has completed born state only
     * status = 0,  OS pushed it in the ready queue but no scheduled
     * status = 1,  The process has been scheduled
     */
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
        if((process[i].at <= time && (process[i].status == -1))) {
            push_back(&v, &process[i]);
            process[i].status = 0; // now it is in the ready queue
        }
    }
}

void cpu(Process *p) {
    p->st = time;
    p->ct = p->st + p->bt;
    p->wt = p->st - p->at;
    p->tt = p->wt + p->bt;
    time = p->ct;
    total_wt += p->wt;
    total_tt += p->tt;
    p->status = 1; // mark it as scheduled
    processedCounter++;
    printf("P%d ", p->pid);
}


Process* scheduler() {
    // get process of minimum BT by following SJF algorithm
    Process *min = NULL, *now = NULL;
    // Get first unscheduled process that is local minimum
    for(int i=0; i<size(&v); i++) {
        Process *now = v.data[i];
        if(now->status == 0) {
            min = now;
            break;
        }
    }
    // Traverse full array to find out global minimum
    if(min != NULL) {
        for(int i=0; i<size(&v); i++) {
            now = v.data[i];
            if((min->bt > now->bt) && (now->status == 0)) min = now;
        }
    }
    return min;
}


void printReadyQueue() {
    printf("PID\tAT\tBT\tStatus\n");
    printf("------------------------------\n");
    for(int i=0; i<size(&v); i++) {
        Process *p = v.data[i];
        printf("P%d\t%d\t%d\t%d\n", p->pid, p->at, p->bt, p->status);
    }
    printf("\n");
}

void printTable(Process p[], int n) {
    printf("PID\tAT\tBT\tWT\tST\tCT\tTT\n");
    printf("--------------------------------------------------\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].st, p[i].ct, p[i].tt);
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
        scanf("%d%d", &process[i].at, &process[i].bt);
        process[i].pid = i+1;
        process[i].status = -1;
    }
    // sort(process, n); // sort processes by arrival time 
    while(processedCounter != n) {
        os(process, n); // using arrival time push to the ready queue
        Process* selectedProcess = scheduler(); // which one need to be scheduled next
        // printReadyQueue();
        if(selectedProcess != NULL) cpu(selectedProcess);
        else time++;
        // printReadyQueue();
    }
    printf("\n\n");
    printTable(process, n);
    printf("Average waiting time = %.3f\n", (float)total_wt / n );
    printf("Average turnaround time = %.3f\n", (float)total_tt / n );
    freeVector(&v);
    return 0;
}