#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int memory[f];
    int last_used[f]; // to store when each frame was last used
    int page_faults = 0;

    // initialize
    for (int i = 0; i < f; i++)
    {
        memory[i] = -1;
        last_used[i] = -1;
    }

    printf("\nPage\tFrames\t\tPage Fault\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        bool hit = false;

        // check for hit
        for (int j = 0; j < f; j++)
        {
            if (memory[j] == page)
            {
                hit = true;
                last_used[j] = i; // update last used time
                break;
            }
        }

        if (!hit)
        {
            int replace_index = -1;
            int lru_time = 9999;

            // find either empty or least recently used
            for (int j = 0; j < f; j++)
            {
                if (memory[j] == -1)
                {
                    replace_index = j;
                    break;
                }
                else if (last_used[j] < lru_time)
                {
                    lru_time = last_used[j];
                    replace_index = j;
                }
            }

            memory[replace_index] = page;
            last_used[replace_index] = i;
            page_faults++;
        }

        // print current frame state
        printf("%d\t", page);
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
    printf("Total Page Hits = %d\n", n - page_faults);

    return 0;
}
