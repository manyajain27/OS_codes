#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, f;
    printf("enter no. of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("\nenter reference string:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("\nenter no. of frames: ");
    scanf("%d", &f);

    int memory[f];
    int front = 0; // initialising the first value to be replaced
    int page_faults = 0, page_hits = 0;

    // initialise memory with -1
    for (int i = 0; i < f; i++)
    {
        memory[i] = -1;
    }

    printf("\nPage\tFrames\t\tPage Fault\n");
    for (int i = 0; i < n; i++)
    {
        int hit = 0;
        for (int j = 0; j < f; j++)
        {
            if (memory[j] == pages[i])
            {
                hit = 1;
                break;
            }
        }

        if (hit == 0)
        {
            memory[front] = pages[i];
            front = (front + 1) % f; // circular to keep fifo fashion
            page_faults++;
        }

        printf("%d\t", pages[i]);
        for (int j = 0; j < f; j++)
        {
            if (memory[j] != -1)
                printf("%d ", memory[j]);
            else
                printf("- ");
        }

        printf("\t\t%s\n", hit ? "Hit" : "Fault");
    }

    printf("\nTotal Page Faults = %d\n", page_faults);
    printf("\nTotal Page Hits = %d\n", (n - page_faults));

    return 0;
}