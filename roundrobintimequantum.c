#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n;
    printf("Enter the number of processes:");
    scanf("%d", &n);
    int bt[n], p[n], s[n], wt[n], tat[n], ts, its[n], tq[n][n], rbt[n], ord[n];
    for (int i = 0; i < n; i++)
    {
        wt[i] = tat[i] = 0;
        s[i] = 1;
        for (int j = 0; j < n; j++)
            tq[i][j] = 0;
    }
    printf("enter the initail timeslice: ");
    scanf("%d", &ts);
    for (int i = 0; i < n; i++)
    {
        ord[i] = i + 1;
        printf("enter the burst time for process%d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("enter the priority for process%d: ", i + 1);
        scanf("%d", &p[i]);
    }

    int flag = 0, j = 0;
    // soting wrt burst time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; i++)
        {
            if (bt[j] > bt[j - 1])
            {
                int t = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = t;

                t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;

                t = ord[j];
                ord[j] = ord[j + 1];
                ord[j + 1] = t;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {

        p[i] += i;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (p[j] > p[j + 1])
            {
                int t = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = t;

                t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;

                t = ord[j];
                ord[j] = ord[j + 1];
                ord[j + 1] = t;
            }
        }
    }
    for (int i = 0; i < n; i++)
        rbt[i] = bt[i];
    while (!flag)
    {
        for (int i = 0; i < n; i++)
        {
            if (p[i] > 0.67 * n)
                p[i] = 0;
            else if (p[i] > 0.33 * n)
                p[i] = 1;
            else
                p[i] = 2;
            if (i != 0)
                if ((bt[i] - bt[i - 1]) > 0)
                    s[i] = 0;
            its[i] = ts + bt[i] + s[i] + p[i];
            if (j == 0)
            {
                if (s[i] == 1)
                    tq[j][i] = its[i];

                else
                    tq[j][i] = ceil(0.5 * (float)its[i]);

                if (rbt[i] < tq[j][i])
                    tq[j][i] = rbt[i];

                rbt[i] = rbt[i] - tq[j][i];
            }
            else
            {
                if (rbt[i] <= 0)
                    tq[j][i] = 0;

                else if (s[i] == 1)
                    tq[j][i] = 2 * tq[j - 1][i];

                else
                    tq[j][i] = 1.5 * tq[j - 1][i];

                if (rbt[i] < tq[j][i])
                    tq[j][i] = rbt[i];

                rbt[i] = rbt[i] - tq[j][i];
            }
        }
        j++;
        flag = -1;
        for (int i = 0; i < n; i++)
            if (rbt[i] > 0)
                flag = 0;
    }
    printf("\n Proces no\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", ord[i]);
    }
    printf("\nBurst timr for processes\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", bt[i]);
    }
    printf("\nIntelligent Time slices\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", its[i]);
    }
    printf("\nDynamic Time quantums\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", tq[i][j]);
        }
        printf(" ");
    }

    for (int x = 0; x < n; x++)
    {
        flag = -1;
        for (int y = 0; y < j; y++)
        {
            for (int z = 0; z < n; z++)
            {
                if (z != x)
                    wt[x] += tq[y][z];
                else if (z == x && tq[y + 1][z] == 0)
                {
                    flag = 0;
                    break;
                }
            }
            tat[x] += tq[y][x];
            if (flag == 0)
                break;
        }
        tat[x] += wt[x];

        printf("\nWaiting time: \n");
        for (int i = 0; i < n; i++)
        {
            printf("%d\t", wt[i]);
        }

        printf("\nTurn Around time: \n");
        for (int i = 0; i < n; i++)
        {
            printf("%d\t", tat[i]);
        }

        float avwt = 0, avtat = 0;
        for (int i = 0; i < n; i++)
        {
            avwt += wt[i];
            avtat += tat[i];
        }
        avwt /= n;
        avtat /= n;

        printf("\nAverage waiting time: %d", avwt);
        printf("\nAverage turnaround time: %d", avtat);
        return 0;
    }
}
