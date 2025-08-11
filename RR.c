#include <stdio.h>
#define N 4
#define time 4

struct RR {
  int id, at, st, bt, wt, ct, tt;
} process[N];

typedef struct RR rr;

bool comp(rr a, rr b) {
   return a.at < b.at;
}

int main() {
  std::cout << "Round Robin Scheduling" << std::endl;
  for(int i=0; i<N; i++) {
    std::cout << "Enter at and bt of process " << (i+1) << ": ";
    std::cin >> process[i].at >> process[i].bt;
    process[i].id = i+1;
  }
  // sorting according to the arrival time
  std::sort(process, process+N, comp);

  // printing after sorting
  for(int i=0; i<N; i++) {
    std::cout << process[i].id << "\t" << process[i].at << "\t" << process[i].bt << std::endl;
  }
  

  return 0;
}