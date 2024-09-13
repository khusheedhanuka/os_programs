#include <stdio.h>
#include <stdlib.h>
#define max 30
void main()
{
    int p[max], bt[max], wt[max], tat[max], n = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("enter the busrt timr for process %d", i + 1);
        scanf("%d", &bt[i]);
    }
}

void findWaitingTime(int bt[], int wt[], int n)
{
    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = bt[i] + wt[i - 1];
    }
}

void findTurnAroundTime(int bt[], int wt[], int n, int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
}

int findAvgTime(int p[], int n, int bt[])
{
}