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
    int page_faults = 0;

    // init memory to -1
    for (int i = 0; i < f; i++)
        memory[i] = -1;

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
                break;
            }
        }

        // if not a hit, replace using optimal logic
        if (!hit)
        {
            int replace_index = -1, farthest = -1;

            for (int j = 0; j < f; j++)
            {
                if (memory[j] == -1)
                {
                    replace_index = j;
                    break;
                }

                // find next use of memory[j]
                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (pages[k] == memory[j])
                        break;
                }

                if (k == n)
                {
                    // not used again
                    replace_index = j;
                    break;
                }
                else if (k > farthest)
                {
                    farthest = k;
                    replace_index = j;
                }
            }

            memory[replace_index] = page;
            page_faults++;
        }

        // print output
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
    printf("Total Page Hits = %d\n", (n - page_faults));

    return 0;
}
