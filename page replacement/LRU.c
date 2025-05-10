#include <stdio.h>

int findLRU(int time[], int f) {
    int min = time[0], pos = 0;
    for(int i = 1; i < f; i++) {
        if(time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[100], frames[100][100], memory[100], time[100];
    int n, f, i, j, counter = 0;
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
        time[i] = 0;
    }

    for(i = 0; i < n; i++) {
        int hit = 0;

        for(j = 0; j < f; j++) {
            if(memory[j] == pages[i]) {
                hit = 1;
                pageHits++;
                counter++;
                time[j] = counter; // update recent use
                break;
            }
        }

        if(!hit) {
            int pos = -1;

            for(j = 0; j < f; j++) {
                if(memory[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if(pos == -1) {
                pos = findLRU(time, f);
            }

            memory[pos] = pages[i];
            counter++;
            time[pos] = counter;
            pageFaults++;
        }

        for(j = 0; j < f; j++) {
            frames[j][i] = memory[j];
        }
    }

    // Horizontal Output
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
