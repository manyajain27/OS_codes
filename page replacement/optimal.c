#include <stdio.h>

int findOptimal(int pages[], int memory[], int n, int index, int f) {
    int farthest = -1, pos = -1;
    for(int i = 0; i < f; i++) {
        int j;
        for(j = index + 1; j < n; j++) {
            if(memory[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        // If not found in future, return immediately
        if(j == n)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int pages[100], frames[100][100], memory[100];
    int n, f, i, j, k;
    int pageFaults = 0, pageHits = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++) {
        memory[i] = -1;
    }

    for(i = 0; i < n; i++) {
        int hit = 0;

        for(j = 0; j < f; j++) {
            if(memory[j] == pages[i]) {
                hit = 1;
                pageHits++;
                break;
            }
        }

        if(!hit) {
            int replacedIndex;

            for(j = 0; j < f; j++) {
                if(memory[j] == -1) {
                    replacedIndex = j;
                    break;
                }
            }

            if(j == f) {
                replacedIndex = findOptimal(pages, memory, n, i, f);
            }

            memory[replacedIndex] = pages[i];
            pageFaults++;
        }

        for(j = 0; j < f; j++) {
            frames[j][i] = memory[j];
        }
    }

    // Horizontal Table Print
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
