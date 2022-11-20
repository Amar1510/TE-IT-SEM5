#include <stdio.h>
int max[10][10], allocation[10][10], need[10][10];
int np, nr;
int avail[10], availableOriginal[10];
int reqResource[10];

void readmatrix(int matrix[10][10], char a[30])
{
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            int temp;
            printf("Enter [%d,%d] of  %s matrix \n", i, j, a);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void display_matrix(int matrix[10][10])
{
    for (int i = 0; i < np; i++)
    {
        printf("\n P%d", i);
        for (int j = 0; j < nr; j++)
        {
            printf(" %d", matrix[i][j]);
        }
    }
}

void calculate_need()
{
    int i, j;
    for (int i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int is_safe()
{
    int i, j, safeIndex = 0, flag;
    int complete[10], safe_seq[10];
    for (i = 0; i < np; i++)
    {
        complete[i] = 0; // Declare all processes as incomplete
    }

    for (i = 0; i < np; i++)
    {
        flag = 0;
        if (complete[i] == 0) // Execute incomplete processes
        {
            for (j = 0; j < nr; j++)
            {
                if (need[i][j] > avail[j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) // need lesser than avail so complete process
            {
                complete[i] = 1;
                safe_seq[safeIndex] = i + 1;
                safeIndex++;
                for (j = 0; j < nr; j++)
                {
                    avail[j] += allocation[i][j];
                }
                i = -1;
            }
        }
    }
    flag = 0;
    for (i = 0; i < np; i++)
    {
        if (complete[i] == 0)
        {
            printf("\n The system is in deadlock");
            flag = 1;
            return 0;
        }
    }
    if (flag == 0)
    {
        printf("\n The system is in safe state! \n safe sequence is ==>");
        for (int i = 0; i < np; i++)
        {
            printf(" P%d", safe_seq[i]);
        }
    }
    return 1;
}

void resource_request()
{
    int processNo;
    printf("\nEnter process number: ");
    scanf("%d", &processNo);

    for (int i = 0; i < nr; i++)
    {
        printf("\nEnter the units of resource [%d] requested: ", i + 1);
        scanf("%d", &reqResource[i]);
    }

    for (int j = 0; j < nr; j++)
    {
        // Checking if resources requested do no cross max needed for that process
        if (reqResource[j] <= max[processNo][j])
        {
            // Checking if resources requested do no cross available resources
            if (reqResource[j] <= avail[j])
            {
                availableOriginal[j] -= reqResource[j];
                allocation[processNo][j] += reqResource[j];
                need[processNo][j] -= reqResource[j];
            }
            else
            {
                printf("\nERROR: Process exceededing available resources!!\nRequest CANNOT be accepted!");
                return;
            }
        }
        else
        {
            printf("\nERROR: Process exceededing maximum limit of resources!!\nRequest CANNOT be accepted!");
            return;
        }
    }
    int status = is_safe();
    if (status == 1)
    {
        printf(" \n+-------------------------------+ REQUEST ACCEPTED +-------------------------------+\n");
    }
    else
    {
        for (int j = 0; j < nr; j++)
        {
            availableOriginal[j] += reqResource[j];
            allocation[processNo][j] -= reqResource[j];
            need[processNo][j] += reqResource[j];
        }

        printf(" \n+-------------------------------+ REQUEST REJECTED +-------------------------------+\n");
        printf(" \n+-------------------------------+ NO SAFE SEQUENCE +-------------------------------+\n");
    }
}

void copyAvail()
{
    for (int i = 0; i < nr; i++)
    {
        availableOriginal[i] = avail[i];
    }
}

int main()
{

    // read input
    printf("\nEnter number of processes : ");
    scanf("%d", &np);
    printf("\nEnter number of resources : ");
    scanf("%d", &nr);

    printf("\nEnter initial allocation matrix: \n");
    readmatrix(allocation, "allocation");

    printf("\nEnter Maximum requirement matrix: \n");
    readmatrix(max, "max needed");

    printf("\nEnter available resources: \n");
    for (int i = 0; i < nr; i++)
    {
        printf("\n Available resource[%d]: ", i + 1);
        scanf("%d", &avail[i]);
    }
    copyAvail();

    // Display input data
    printf("\n~~~~~~~~~~~~~~~~~Entered Data is ~~~~~~~~~~~~~\n\n");
    printf("\n Initial allocation:\n");
    display_matrix(allocation);
    printf("\n\n\n Maximum Requirement:\n");
    display_matrix(max);
    printf("\n\n\n Available Resources:\n");
    for (int i = 0; i < nr; i++)
    {
        printf("\n Available resource[%d]: ", i + 1);
        printf("%d", avail[i]);
    }

    // calculate and display need
    calculate_need();
    printf("\n\n\n Need matrix:\n");
    display_matrix(need);

    // Execute processes using Bankers Algorithm
    is_safe();
    
    //run for resource request
    while (1)
    {
        printf(" \n+-------------------------------+ MENU  +-------------------------------+\n");
        printf("\n1) Press'+' to enter new request.\n2) Press '-' to terminate. \n");
        char choice;
        scanf("%c", &choice);
        if (choice == '+')
        {
            resource_request();
        }
        else if (choice == '-')
        {
            break;
        }
    }
    printf("\n +-------------------------------+ THANK YOU  +-------------------------------+\n");
    return 0;
}