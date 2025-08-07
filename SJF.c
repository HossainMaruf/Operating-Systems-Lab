#include <stdio.h>

typedef struct {
    int p, at, bt, wt, st, ct, tt;
} Process;

int total_wt=0, total_tt=0, idleTime=0;

void printTable(Process process[], int n) {
    printf("Process\tAT\tBT\tWT\tST\tCT\tTT\n");
    printf("--------------------------------------------------\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", process[i].p, process[i].at, process[i].bt, process[i].wt, process[i].st, process[i].ct, process[i].tt);
    }
    printf("\n");
}

void main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    Process process[n];
    for(int i=0; i<n; i++) {
        process[i].p = i+1;
        scanf("%d%d", &process[i].at, &process[i].bt);
    }

    // printTable(process, n);

    // Sorting (Bubble Sort)
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-1-i; j++) {
            if(process[j].at > process[j+1].at) {
                Process temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }

    // printTable(process, n);
    // FCFS Start
    for(int i=0; i<n; i++) {
        if(i == 0) {
            // First Process
            process[i].st = process[i].at;
        } else {
            // Not the first process
            if(process[i-1].ct < process[i].at) {
                process[i].st = process[i].at;
                // There is idle time
                idleTime += (process[i].at - process[i-1].ct);
            } else process[i].st = process[i-1].ct;
        }
        process[i].wt = process[i].st - process[i].at;
        process[i].ct = process[i].st + process[i].bt;
        process[i].tt = process[i].wt + process[i].bt;
        total_wt += process[i].wt;
        total_tt += process[i].tt;
    }
    printTable(process, n);
    printf("\nAverage waiting time = %0.3f", (float)total_wt/n);
    printf("\nAverage turnaround time = %0.3f", (float)total_tt/n);
    printf("\nIdle Time = %d", idleTime);
}