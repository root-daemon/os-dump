#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int priority;
};

void priority_scheduling(struct Process processes[], int n) {
    // Sort processes by priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int wait_time = 0, total_wait_time = 0, total_turnaround_time = 0;
    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        int turnaround_time = wait_time + processes[i].burst_time;
        total_wait_time += wait_time;
        total_turnaround_time += turnaround_time;

        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].priority, processes[i].burst_time, wait_time, turnaround_time);

        wait_time += processes[i].burst_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time and priority for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].priority);
    }

    priority_scheduling(processes, n);
    return 0;
}
