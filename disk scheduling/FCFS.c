#include <stdio.h>
#include <stdlib.h>

int main() {
    int total_tracks, n, i, current_position, total_movement = 0;

    // Ask for total number of tracks
    printf("Enter the total number of tracks (e.g., 200): ");
    scanf("%d", &total_tracks);

    // Ask for number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    // Input requests
    printf("Enter the disk requests (between 0 and %d):\n", total_tracks - 1);
    for(i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if(requests[i] < 0 || requests[i] >= total_tracks) {
            printf("Invalid track number! Must be between 0 and %d.\n", total_tracks - 1);
            return 1;
        }
    }

    // Input initial head position
    printf("Enter the initial head position (between 0 and %d): ", total_tracks - 1);
    scanf("%d", &current_position);
    if(current_position < 0 || current_position >= total_tracks) {
        printf("Invalid head position! Must be between 0 and %d.\n", total_tracks - 1);
        return 1;
    }

    // Process requests
    printf("\nSequence of head movements:\n");
    for(i = 0; i < n; i++) {
        printf("From %d to %d\n", current_position, requests[i]);
        total_movement += abs(requests[i] - current_position); //mod operator
        current_position = requests[i];
    }

    printf("\nTotal head movement = %d tracks\n", total_movement);

    return 0;
}
