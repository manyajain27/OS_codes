#include <stdio.h>

int main() {
    int n = 4;
    int process[] = {1, 2, 3, 4};
    int arrival[] = {0, 1, 5, 6};
    int burst[] = {2, 2, 3, 4};
    int completion[4], tat[4], wt[4];
    int time = 0;
    float total_tat = 0, total_wt = 0;

    // FCFS Scheduling (already in arrival order)
    for(int i = 0; i < n; i++) {
        if(time < arrival[i]) {
            time = arrival[i]; // CPU is idle
        }
        time += burst[i];
        completion[i] = time;
        tat[i] = completion[i] - arrival[i];
        wt[i] = tat[i] - burst[i];
        total_tat += tat[i];
        total_wt += wt[i];
    }

    // Output Table
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    printf("----------------------\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrival[i], burst[i], completion[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT: %.2f", total_tat / n);
    printf("\nAverage WT: %.2f\n", total_wt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < arrival[i]) {
            printf(" IDLE |");
            time = arrival[i];
        }
        printf(" P%d |", process[i]);
        time += burst[i];
    }

    // Timeline
    printf("\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < arrival[i]) {
            time = arrival[i];
            printf("      %d", time);
        }
        time += burst[i];
        printf("    %d", time);
    }

    return 0;
}
