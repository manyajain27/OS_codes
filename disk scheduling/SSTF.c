#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the index of the closest request
int findClosestRequest(int requests[], int visited[], int n, int current_position) {
    int min_distance = INT_MAX;
    int index = -1;

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            int distance = abs(requests[i] - current_position);
            if(distance < min_distance) {
                min_distance = distance;
                index = i;
            }
        }
    }

    return index;
}

int main() {
    int total_tracks, n, i, total_movement = 0, current_position;

    printf("Enter the total number of tracks (e.g., 200): ");
    scanf("%d", &total_tracks);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n], visited[n];

    printf("Enter the disk requests (between 0 and %d):\n", total_tracks - 1);
    for(i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if(requests[i] < 0 || requests[i] >= total_tracks) {
            printf("Invalid track number! Must be between 0 and %d.\n", total_tracks - 1);
            return 1;
        }
        visited[i] = 0; // Mark all as unvisited
    }

    printf("Enter the initial head position (between 0 and %d): ", total_tracks - 1);
    scanf("%d", &current_position);
    if(current_position < 0 || current_position >= total_tracks) {
        printf("Invalid head position! Must be between 0 and %d.\n", total_tracks - 1);
        return 1;
    }

    printf("\nSequence of head movements:\n");
    for(i = 0; i < n; i++) {
        int idx = findClosestRequest(requests, visited, n, current_position);
        if(idx == -1) break;

        printf("From %d to %d\n", current_position, requests[idx]);
        total_movement += abs(requests[idx] - current_position);
        current_position = requests[idx];
        visited[idx] = 1; // Mark as visited
    }

    printf("\nTotal head movement = %d tracks\n", total_movement);

    return 0;
}
