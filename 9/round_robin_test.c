#include <stdlib.h>

struct Process
{
    int id;
    int burst_time;
    int remaining_time;
    int waiting_time;
};

void round_robin(struct Process processes[], int n, int time_slice)
{
    int time = 0;
    int completed = 0;

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time > 0)
            {
                if (processes[i].remaining_time <= time_slice)
                {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                }
                else
                {
                    time += time_slice;
                    processes[i].remaining_time -= time_slice;
                }
            }
        }
    }
}
