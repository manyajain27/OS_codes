#include <stdio.h>

#define MAX 100

int main() {
    int blockSize[MAX], processSize[MAX], allocation[MAX];
    int m, n, i, j;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    
    printf("Enter the size of each memory block:\n");
    for (i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the size of each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1; // Initially not allocated
    }

    // First Fit Allocation
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    // Output Allocation Results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    // Remaining Holes
    printf("\nRemaining size of memory blocks (holes):\n");
    for (i = 0; i < m; i++) {
        printf("Block %d: %d\n", i + 1, blockSize[i]);
    }

    return 0;
}
