#include <stdio.h>

struct Process{
    int id;
    int burst_time;
    int priority;
};

void priority_sheduling(struct Process processes[], int n){
    
    //sort the priority in order
    for (int i =0;i<n-1;i++){
        for(int j=i+1;j<n-1;j++){
            if(processes[i].priority>processes[j].priority){
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j]= temp;
            }
        }
    }

    int wait_time=0, total_wait_time=0, total_turnaround_time=0;
    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0;i<n;i++){
        int turnaround_time = wait_time+ processes[i].burst_time;
        total_wait_time+=wait_time;
        total_turnaround_time+=turnaround_time;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].priority, processes[i].burst_time, wait_time, turnaround_time);

        wait_time+=processes[i].burst_time;
    }
}