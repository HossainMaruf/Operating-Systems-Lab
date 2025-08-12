/**
 * Problem 1: https://www.guru99.com/shortest-job-first-sjf-scheduling.html 
 * Problem 2: https://www.tutorialspoint.com/operating_system/os_shortest_job_first_scheduling.htm
 * Problem 3: https://www.gatevidyalay.com/sjf-scheduling-srtf-cpu-scheduling/
 */ 
#include <stdio.h>
#include <stdbool.h>
#include "vector.h"
Vector v;

int time = 0, idleTime = 0, total_wt = 0, total_tt = 0, processedCounter = 0;
typedef struct {
    int pid, at, bt, rt, wt, st, ct, tt, status, isPreempted;
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
            if((min->rt > now->rt) && (now->status == 0)) min = now;
        }
    }
    return min;
}

void cpu(Process *p, Process process[], int n) {
    if(p->st == -1) {
        p->st = time; // start execution
        p->wt = p->st - p->at;
    }
    if(p->isPreempted == true) { p->wt += (time - p->ct); } 

    time++; // exexute for only 1 second
    p->rt -= 1; // decrease remaining time by 1 second

    os(process, n);
    Process *hasProcess = scheduler();
    if(hasProcess != NULL && (hasProcess->pid == p->pid)) {
        // no process without running process
        if(p->rt == 0) {
            // The process has no remaining time to schedule
            processedCounter++;
            p->status = 1;
            p->isPreempted = false;
            p->ct = time; // now it is complete
            p->tt = p->wt + p->bt;
            total_wt += p->wt;
            total_tt += p->tt;
        } else {
            p->isPreempted = false;
            cpu(p, process, n);
        } 
    } else if(hasProcess != NULL && (hasProcess->pid != p->pid)) {
        // There is a process of higher priority
        // make preemption
        p->isPreempted = true;
        p->ct = time; // temporary completion time
    } else if(hasProcess == NULL) return;
    printf("P%d ", p->pid);
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
    printf("PID\tAT\tBT\tWT\tST\tCT\tTT\tRT\n");
    printf("--------------------------------------------------\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].st, p[i].ct, p[i].tt, p[i].rt);
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
        process[i].st = -1; // Flag to detect how many times it is pushed to queue
        process[i].rt = process[i].bt;
        process[i].isPreempted = false;
    }
    // sort(process, n); // sort processes by arrival time 
    while(processedCounter != n) {
        os(process, n); // using arrival time push to the ready queue
        Process* selectedProcess = scheduler(); // which one need to be scheduled next
        // printReadyQueue();
        if(selectedProcess != NULL) cpu(selectedProcess, process, n);
        else { time++; idleTime++; };
        // printReadyQueue();
    }
    printf("\n\n");
    printTable(process, n);
    printf("Average waiting time = %.3f\n", (float)total_wt / n );
    printf("Average turnaround time = %.3f\n", (float)total_tt / n );
    printf("Idle time = %d\n", idleTime);
    freeVector(&v);
    return 0;
}