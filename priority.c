#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct
{
    int pid;
    int burst_time;
    int priority;
} process;

void swap(process *a, process *b)
{
    process temp = *a;
    *a = *b;
    *b = temp;
}

void sort_by_priority(process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].priority > p[j].priority)
            {
                swap(&p[i], &p[j]);
            }
        }
    }
}

void print_gantt_chart(process *p, int n)
{
    int current_time = 0;
    printf("Gantt chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].burst_time; j++)
        {
            printf("-");
            current_time++;
        }
        printf(" ");
    }
    printf("\n");
    printf("|");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].burst_time - 1; j++)
        {
            printf(" ");
        }
        printf("P%d", p[i].pid);
        for (int j = 0; j < p[i].burst_time - 1; j++)
        {
            printf(" ");
        }
        printf("|");
    }
    printf("\n");
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].burst_time; j++)
        {
            printf("-");
        }
        printf(" ");
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].burst_time; j++)
        {
            printf(" ");
        }
        if (current_time < 10)
        {
            printf("%d", current_time);
        }
        else
        {
            printf("%d", current_time / 10);
            printf("%d", current_time % 10);
        }
    }
    printf("\n");
}

void calculate_waiting_time(process *p, int n, int *wt)
{
    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = p[i - 1].burst_time + wt[i - 1];
    }
}

void calculate_turnaround_time(process *p, int n, int *wt, int *tat)
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = p[i].burst_time + wt[i];
    }
}

void calculate_average_times(process *p, int n)
{
    int wt[MAX_PROCESSES], tat[MAX_PROCESSES], total_wt = 0, total_tat = 0;
    calculate_waiting_time(p, n, wt);
    calculate_turnaround_time(p, n, wt, tat);
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, p[i].priority, wt[i], tat[i]);
        total_wt += wt[i];
