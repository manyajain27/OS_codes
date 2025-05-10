#include <stdio.h>
#define N 4

int main() {
    int process[] = {1, 2, 3, 4};
    int arrival[] = {0, 1, 2, 4};
    int burst[] = {5, 4, 2, 1};
    int remaining[N];
    int completion[N], tat[N], wt[N];
    int time = 0, tq = 2;
    int done = 0;

    for (int i = 0; i < N; i++) {
        remaining[i] = burst[i];
    }

    int isDone[N] = {0}; // Track if a process is completed
    int total_tat = 0, total_wt = 0;

    printf("Gantt Chart:\n|");

    while (done < N) {
        int executed = 0;

        for (int i = 0; i < N; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                int execTime = (remaining[i] > tq) ? tq : remaining[i];
                printf(" P%d |", process[i]);
                time += execTime;
                remaining[i] -= execTime;
                executed = 1;

                if (remaining[i] == 0 && !isDone[i]) {
                    completion[i] = time;
                    tat[i] = completion[i] - arrival[i];
                    wt[i] = tat[i] - burst[i];
                    total_tat += tat[i];
                    total_wt += wt[i];
                    done++;
                    isDone[i] = 1;
                }
            }
        }

        if (!executed) {
            printf(" IDLE |");
            time++;
        }
    }

    // Print Timeline
    printf("\n0");
    time = 0;
    int timeline[N*10], k = 0; // Just to hold time points for display
    for (int i = 0; i < N; i++) remaining[i] = burst[i]; // Reset for timeline

    done = 0;
    while (done < N) {
        int executed = 0;

        for (int i = 0; i < N; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                int execTime = (remaining[i] > tq) ? tq : remaining[i];
                time += execTime;
                timeline[k++] = time;
                remaining[i] -= execTime;
                executed = 1;

                if (remaining[i] == 0) {
                    done++;
                }
            }
        }

        if (!executed) {
            time++;
            timeline[k++] = time;
        }
    }

    for (int i = 0; i < k; i++) {
        printf("   %d", timeline[i]);
    }

    // Output Table
    printf("\n\nP\tAT\tBT\tCT\tTAT\tWT\n");
    printf("------------------------------\n");
    for (int i = 0; i < N; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrival[i], burst[i], completion[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT: %.2f", (float)total_tat / N);
    printf("\nAverage WT: %.2f\n", (float)total_wt / N);

    return 0;
}
