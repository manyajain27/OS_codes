#include <stdio.h>

int main() {
    int pages[100], frames[100][100], n, f, i, j, k = 0;
    int pageFaults = 0, pageHits = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int memory[f];
    for(i = 0; i < f; i++) {
        memory[i] = -1;
    }

    for(i = 0; i < n; i++) {
        int hit = 0;

        // Check for hit
        for(j = 0; j < f; j++) {
            if(memory[j] == pages[i]) {
                hit = 1;
                pageHits++;
                break;
            }
        }

        // If miss, replace using FIFO
        if(hit == 0) {
            memory[k] = pages[i];
            k = (k + 1) % f;
            pageFaults++;
        }

        // Store current memory state
        for(j = 0; j < f; j++) {
            frames[j][i] = memory[j];
        }
    }

    // Print horizontal table
    printf("\nPage Reference String:\n");
    for(i = 0; i < n; i++) {
        printf(" %2d ", pages[i]);
    }

    printf("\n");
    for(i = f - 1; i >= 0; i--) {
        printf("F%d |", i + 1);
        for(j = 0; j < n; j++) {
            if(frames[i][j] == -1)
                printf(" --");
            else
                printf(" %2d", frames[i][j]);
        }
        printf("\n");
    }

    float hitRatio = (float)pageHits / n;
    float missRatio = (float)pageFaults / n;

    printf("\nPage Hits: %d\n", pageHits);
    printf("Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %d/%d = %.2f\n", pageHits, n, hitRatio);
    printf("Miss Ratio: %d/%d = %.2f\n", pageFaults, n, missRatio);

    return 0;
}
