#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int waiting_time;
};

void round_robin(struct Process processes[], int n, int time_slice) {
    int time = 0;          // Current time
    int completed = 0;     // Number of processes completed

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= time_slice) {
                    // Process can complete in this time slice
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    completed++;
                } else {
                    // Process requires more than one time slice
                    time += time_slice;
                    processes[i].remaining_time -= time_slice;
                }
            }
        }
    }

    // Calculate total waiting time
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() {
    int n, time_slice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
    }

    printf("Enter time slice: ");
    scanf("%d", &time_slice);

    round_robin(processes, n, time_slice);
    return 0;
}
