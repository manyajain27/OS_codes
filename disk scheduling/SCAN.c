#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    // Simple bubble sort for small inputs
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main() {
    int total_tracks, n, i, head, direction;
    int total_movement = 0;

    printf("Enter total number of tracks (e.g., 200): ");
    scanf("%d", &total_tracks);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n + 1]; // +1 for boundary end
    int left[n], right[n];
    int left_count = 0, right_count = 0;

    printf("Enter the disk requests (between 0 and %d):\n", total_tracks - 1);
    for(i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if(requests[i] < 0 || requests[i] >= total_tracks) {
            printf("Invalid request! Must be between 0 and %d.\n", total_tracks - 1);
            return 1;
        }
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);
    if(head < 0 || head >= total_tracks) {
        printf("Invalid head position! Must be between 0 and %d.\n", total_tracks - 1);
        return 1;
    }

    printf("Enter direction (0 = left, 1 = right): ");
    scanf("%d", &direction);

    // Separate requests to left and right of head
    for(i = 0; i < n; i++) {
        if(requests[i] < head)
            left[left_count++] = requests[i];
        else
            right[right_count++] = requests[i];
    }

    // Sort both sides
    sort(left, left_count);
    sort(right, right_count);

    printf("\nSequence of head movements:\n");

    if(direction == 1) { // Moving right
        for(i = 0; i < right_count; i++) {
            printf("From %d to %d\n", head, right[i]);
            total_movement += abs(right[i] - head);
            head = right[i];
        }
        // Go to last track if not already there
        if(head != total_tracks - 1) {
            printf("From %d to %d (end)\n", head, total_tracks - 1);
            total_movement += abs((total_tracks - 1) - head);
            head = total_tracks - 1;
        }
        for(i = left_count - 1; i >= 0; i--) {
            printf("From %d to %d\n", head, left[i]);
            total_movement += abs(left[i] - head);
            head = left[i];
        }
    } else { // Moving left
        for(i = left_count - 1; i >= 0; i--) {
            printf("From %d to %d\n", head, left[i]);
            total_movement += abs(left[i] - head);
            head = left[i];
        }
        if(head != 0) {
            printf("From %d to 0 (start)\n", head);
            total_movement += head;
            head = 0;
        }
        for(i = 0; i < right_count; i++) {
            printf("From %d to %d\n", head, right[i]);
            total_movement += abs(right[i] - head);
            head = right[i];
        }
    }

    printf("\nTotal head movement = %d tracks\n", total_movement);

    return 0;
}
