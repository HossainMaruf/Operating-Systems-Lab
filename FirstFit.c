#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  int nb, nf;

  printf("Memory Management Scheme - First Fit\n");

  printf("Enter the number of blocks: ");
  scanf("%d", &nb); // take how many blocks
  int blocks[nb+1], blocks_flag[nb+1], answer[nb+1], fragmentation[nb+1];
  blocks[0] = -1;
  printf("Enter the size of the blocks.\n"); // enter each block size
  for (int i = 1; i <= nb; i++) {
    printf("Block %d:", i);
    scanf("%d", &blocks[i]);
  }

  printf("Enter the number of files: "); // take how many files or process
  scanf("%d", &nf);
  int files[nf+1], files_flag[nf+1];
  files[0] = -1;
  printf("Enter the size of the files.\n"); // enter each file or process size
  for (int i = 1; i <= nf; i++) {
    printf("File %d:", i);
    scanf("%d", &files[i]);
  }
  // SET ALL THE MEMORY
  memset(blocks_flag, -1, (nb+1)*sizeof(int)); // you can use for loop
  memset(answer, -1, (nb+1)*sizeof(int)); // you can use for loop
  memset(fragmentation, -1, (nb+1)*sizeof(int)); // you can use for loop

  memset(files_flag, -1, (nf+1)*sizeof(int)); // you can use for loop

  for (int i = 1; i <= nf; i++) {
    for (int j = 1; j <= nb; j++) {
      if (blocks_flag[j] == -1 && (blocks[j] >= files[i])) {
        answer[j] = i;
        files_flag[i] = 1;
        blocks_flag[j] = 1;
        fragmentation[j] = blocks[j] - files[i];
        break;
      }
    }
  }

  printf("\nBlockNo:\tBlockSize:\tFileNo:\t\tFileSize:\tFragement");
  for (int i = 1; i <= nb; i++)
    printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, blocks[i], answer[i], answer[i] == -1 ? -1 : files[answer[i]], fragmentation[i]);
  return 0;
}