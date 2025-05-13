#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int main() {
    int n = 4;
    int process[] = {1, 2, 3, 4};
    int arrival[] = {0, 1, 2, 3};
    int burst[] = {5, 3, 1, 2};
    int remaining[4], completion[4], tat[4], wt[4];
    bool done[4] = {false};
    bool in_queue[4] = {false};

    int tq = 2;
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    // Ready Queue
    int queue[MAX];
    int front = 0, rear = 0;

    // Initialize remaining burst
    for (int i = 0; i < n; i++)
        remaining[i] = burst[i];

    // Add first arriving processes
    for (int i = 0; i < n; i++) {
        if (arrival[i] == 0) {
            queue[rear++] = i;
            in_queue[i] = true;
        }
    }

    printf("Gantt Chart:\n");

    while (completed < n) {
        if (front == rear) {
            printf("IDLE ");
            time++;
            for (int i = 0; i < n; i++) {
                if (arrival[i] <= time && !done[i] && !in_queue[i]) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = queue[front++];
        in_queue[idx] = false;

        int run_time = (remaining[idx] < tq) ? remaining[idx] : tq;

        for (int t = 0; t < run_time; t++) {
            printf("P%d ", process[idx]);
            time++;

            // Add newly arrived processes
            for (int i = 0; i < n; i++) {
                if (arrival[i] == time && !done[i] && !in_queue[i]) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                }
            }
        }

        remaining[idx] -= run_time;

        if (remaining[idx] == 0) {
            completion[idx] = time;
            tat[idx] = completion[idx] - arrival[idx];
            wt[idx] = tat[idx] - burst[idx];
            total_tat += tat[idx];
            total_wt += wt[idx];
            done[idx] = true;
            completed++;
        } else {
            queue[rear++] = idx;
            in_queue[idx] = true;
        }
    }

    printf("\n\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i], arrival[i], burst[i], completion[i], tat[i], wt[i]);
    }

    printf("\nAvg TAT: %.2f", total_tat / n);
    printf("\nAvg WT: %.2f\n", total_wt / n);

    return 0;
}
