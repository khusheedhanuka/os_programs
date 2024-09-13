#include <stdio.h>
#include <stdlib.h>
void main()
{
    int bt[10], wt[10], tat[10], p[10], at[10];
    int n;
    printf("enter the no of processes");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
        p[i] = i + 1;
    }
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (bt[j] > bt[j + 1])
            {
                temp = bt[j + 1];
                bt[j + 1] = bt[j];
                bt[j] = temp;

                temp = at[j + 1];
                at[j + 1] = at[j];
                at[j] = temp;

                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }
        }
    }
    printf("Process\t|\tArrivalTime\t|\tBurstTime\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t|\t%d\t|\t%d\n", p[i], at[i], bt[i]);
    }
}
