#include <stdio.h>
#include <stdbool.h>

int main(){
    int n=4;
    int process[] = {1,2,3,4};
    int arrival[] = {1,2,1,4};
    int burst[] = {3,4,2,4};
    int completion[4], tat[4], wt[4];
    bool done[4] = {false};
    int time = 0;
    int completed = 0; //to check if all processes are done or not
    float total_tat=0, total_wt=0;
    

    
    //main logic
    printf("Gantt Chart: \n");
    
    while(completed<n){
        int index = -1;
        int min_bt = 999;
        
        //shortest burst time and not completed yet
        for(int i=0; i<n; i++){
            if(arrival[i]<=time && !done[i] && burst[i]<min_bt){
                min_bt= burst[i];
                index = i;
            }
        }
        
        if(index == -1){
            printf("IDLE ");
            time++;
        }
        else{
            time+=burst[index];
            completion[index] = time;
            tat[index] = completion[index] - arrival[index];
            wt[index] = tat[index] - burst[index];
            total_tat+=tat[index];
            total_wt+=wt[index];
            done[index] = true;
            completed++;
            printf("P%d ", process[index]);
        }
        
    }
    
    printf("\n\nP\tAT\tBT\tCT\tTAT\tWT\n");
    printf("----------------------\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrival[i], burst[i], completion[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT: %.2f", total_tat / n);
    printf("\nAverage WT: %.2f\n", total_wt / n );
    
    return 0;
}