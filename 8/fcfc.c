#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void fcfs_scheduling(struct Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            processes[i].waiting_time = 0;
        } else {
            processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        }

        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    fcfs_scheduling(processes, n);
    return 0;
}
