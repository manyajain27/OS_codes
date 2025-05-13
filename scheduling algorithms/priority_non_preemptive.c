#include <stdio.h>
#include <stdbool.h>

int main() {
    int n = 4;
    int process[] = {1, 2, 3, 4};
    int arrival[] = {0, 1, 2, 3};
    int burst[] = {5, 3, 1, 2};
    int priority[] = {2, 1, 4, 3}; // lower = higher priority

    int completion[4], tat[4], wt[4];
    bool done[4] = {false};

    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("Gantt Chart:\n");

    while(completed < n) {
        int idx = -1;
        int best_priority = 999;

        for(int i = 0; i < n; i++) {
            if(arrival[i] <= time && !done[i]) {
                if(priority[i] < best_priority) {
                    best_priority = priority[i];
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            printf("IDLE ");
            time++;
        } else {
            printf("P%d ", process[idx]);
            time += burst[idx];
            completion[idx] = time;
            tat[idx] = completion[idx] - arrival[idx];
            wt[idx] = tat[idx] - burst[idx];
            total_tat += tat[idx];
            total_wt += wt[idx];
            done[idx] = true;
            completed++;
        }
    }

    printf("\n\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i], arrival[i], burst[i], priority[i],
               completion[i], tat[i], wt[i]);
    }

    printf("\nAvg TAT: %.2f", total_tat / n);
    printf("\nAvg WT: %.2f\n", total_wt / n);

    return 0;
}
