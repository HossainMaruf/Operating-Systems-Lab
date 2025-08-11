// Banker's Algorithm  
#include <stdio.h>  
int main()  
{  
    // P0, P1, P2, P3, P4 are the Process names here  
    int index=0;
    int n = 5, m = 3; // Number of processes and resources
    // Available Resources (Initial)
    int avail[m] = {10, 5, 7};  
    int current_need[n][m], flag[n], ans[n]; // ans[] will contain the process sequence
    // Allocation Matrix
    // MAX Matrix 
    int max_need[n][m] = {{7, 5, 3},  // P0 
                          {3, 2, 2},  // P1  
                          {9, 0, 2},  // P2  
                          {2, 2, 2},  // P3  
                          {4, 3, 3}}; // P4  
    int allocated[n][m] = {{0, 1, 0},  // P0   
                           {2, 0, 0},  // P1  
                           {3, 0, 2},  // P2  
                           {2, 1, 1},  // P3  
                           {0, 0, 2}}; // P4  
    // Calculating the current need of resources
    for (int i = 0; i < n; i++)  {  
        flag[i] = 0; // all the process is unscheduled  
        for (int j = 0; j < m; j++)  
            current_need[i][j] = max_need[i][j] - allocated[i][j];  
    }  
    // calculating available resouce after first allocation by OS
    for(int i=0; i<m; i++) {
      for(int j=0; j<n; j++) {
        avail[i] -= allocated[j][i];
      }
    } 
    /**
     * Now available resouce are avail[] = {3, 3, 2}
    */

    for (int scan = 0; scan < n; scan++) { // scan n times for scheduling the process 
        for (int i = 0; i < n; i++) { // iterate each process 
            if (flag[i] == 0) { // if it is not scheduled 
                int f = 1;  // suppose, it can be scheduled
                for (int j = 0; j < m; j++) {  
                    if (current_need[i][j] > avail[j]) {  
                        f = 0; // no, it can not be scheduled for insufficient resource 
                        break;  
                    }  
                }  
                if (f == 1) { // yes, it was scheduled 
                    ans[index++] = i; // push the process in sequence  
                    for (int k = 0; k < m; k++) // return the resources 
                        avail[k] += allocated[i][k];  
                    flag[i] = 1; // mark it as scheduled process 
                }  
            }  
        }  
    }  
    int safe = 1;  // suppose, the system is safe
    for (int i = 0; i < n; i++) {  
        if (flag[i] == 0) { // true means 0th process was not scheduled for insufficient resource 
            safe = 0;  
            printf("The following system is not safe\n");  
            break;  
        }  
    }  
    if (safe == 1) { // yes, system is safe 
        printf("Following is the SAFE Sequence\n");  
        for (int i = 0; i < n; i++)  
          if(i != n-1) printf("P%d -> ", ans[i]);  
          else printf("P%d", ans[i]);
      }  
    return (0);  
}  