#include <stdio.h>

int main() {
    int n = 4;
    int process[] = {1, 2, 3, 4};
    int arrival[] = {1, 2, 1, 4};
    int burst[] = {3, 4, 2, 4};
    int completion[4], tat[4], wt[4];
    int remaining[4], is_completed[4] = {0};
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
    
    // Copy burst times to remaining times
    for(int i = 0; i < n; i++) {
        remaining[i] = burst[i];
    }
    
    // Store the execution sequence for Gantt chart
    int exec_sequence[100]; // Assuming max execution steps won't exceed 100
    int exec_time[100];
    int seq_idx = 0;
    
    // SJF Non-preemptive Scheduling
    while(completed != n) {
        int min_burst = 9999;
        int min_idx = -1;
        int idle_time = 0;
        
        // Find the process with minimum burst time among arrived processes
        for(int i = 0; i < n; i++) {
            if(arrival[i] <= time && is_completed[i] == 0) {
                if(burst[i] < min_burst) {
                    min_burst = burst[i];
                    min_idx = i;
                }
                // If burst times are equal, prioritize the process that arrived earlier
                else if(burst[i] == min_burst && arrival[i] < arrival[min_idx]) {
                    min_idx = i;
                }
            }
        }
        
        // If no process is available at current time, move time to next arrival
        if(min_idx == -1) {
            time++;
            continue;
        }
        
        // Record execution for Gantt chart
        exec_sequence[seq_idx] = process[min_idx];
        exec_time[seq_idx] = time;
        seq_idx++;
        
        // Execute the selected process
        time += burst[min_idx];
        completion[min_idx] = time;
        tat[min_idx] = completion[min_idx] - arrival[min_idx];
        wt[min_idx] = tat[min_idx] - burst[min_idx];
        
        total_tat += tat[min_idx];
        total_wt += wt[min_idx];
        
        is_completed[min_idx] = 1;
        completed++;
    }
    
    // Record the final time for Gantt chart
    exec_time[seq_idx] = time;
    
    // Output Table
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    printf("----------------------\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrival[i], burst[i], completion[i], 
               tat[i], wt[i]);
    }
    
    printf("\nAverage TAT: %.2f", total_tat / n);
    printf("\nAverage WT: %.2f\n", total_wt / n);
    
    // Gantt Chart
    printf("\nGantt Chart:\n|");
    
    int prev_time = 0;
    for(int i = 0; i < seq_idx; i++) {
        // Check if there's idle time between processes
        if(exec_time[i] > prev_time) {
            printf(" IDLE |");
        }
        printf(" P%d |", exec_sequence[i]);
        prev_time = exec_time[i] + burst[process[exec_sequence[i]-1]-1];
    }
    
    // Timeline
    printf("\n%d", 0);
    prev_time = 0;
    for(int i = 0; i < seq_idx; i++) {
        // Print idle time marker if any
        if(exec_time[i] > prev_time) {
            printf("      %d", exec_time[i]);
        }
        // Print process completion time
        printf("    %d", exec_time[i] + burst[process[exec_sequence[i]-1]-1]);
        prev_time = exec_time[i] + burst[process[exec_sequence[i]-1]-1];
    }
    
    return 0;
}