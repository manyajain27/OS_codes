#include <stdio.h>

int main() {
    int n = 4;
    int process[] = {1, 2, 3, 4};
    int arrival[] = {0, 1, 2, 4};
    int burst[] = {5, 3, 4, 1};
    int remaining[4];
    int completion[4], tat[4], wt[4];
    int is_completed[4] = {0};
    
    for (int i = 0; i < n; i++) {
        remaining[i] = burst[i];
    }

    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    // Gantt chart arrays
    int gantt_process[100], gantt_time[100];
    int gantt_idx = 0;

    int last_process = -1;

    while (completed != n) {
        int index = -1;
        int min_rem = 9999;

        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && is_completed[i] == 0) {
                if (remaining[i] < min_rem) {
                    min_rem = remaining[i];
                    index = i;
                }
                // Tie-breaker: if equal remaining time, earlier arrival
                else if (remaining[i] == min_rem && arrival[i] < arrival[index]) {
                    index = i;
                }
            }
        }

        if (index != -1) {
            remaining[index]--;
            if (last_process != index) {
                gantt_process[gantt_idx] = process[index];
                gantt_time[gantt_idx] = time;
                gantt_idx++;
                last_process = index;
            }

            if (remaining[index] == 0) {
                completion[index] = time + 1;
                tat[index] = completion[index] - arrival[index];
                wt[index] = tat[index] - burst[index];

                total_tat += tat[index];
                total_wt += wt[index];

                is_completed[index] = 1;
                completed++;
            }
        } else {
            // CPU is idle
            if (last_process != -2) {
                gantt_process[gantt_idx] = -1; // idle
                gantt_time[gantt_idx] = time;
                gantt_idx++;
                last_process = -2;
            }
        }

        time++;
    }
    gantt_time[gantt_idx] = time;

    // Print Table
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrival[i], burst[i], completion[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT: %.2f", total_tat / n);
    printf("\nAverage WT: %.2f", total_wt / n);

    // Gantt Chart
    printf("\n\nGantt Chart:\n|");
    for (int i = 0; i < gantt_idx; i++) {
        if (gantt_process[i] == -1)
            printf(" IDLE |");
        else
            printf(" P%d |", gantt_process[i]);
    }

    printf("\n");
    for (int i = 0; i <= gantt_idx; i++) {
        printf("%-5d", gantt_time[i]);
    }

    return 0;
}
