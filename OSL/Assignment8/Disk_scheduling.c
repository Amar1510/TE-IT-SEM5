#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int choice, track, no_req, head, head1, distance;

int disc_req[100], finish[100];

void menu()
{
    printf("\n\n********MENU********");
    printf("\n 1. Input data\n 2. SSTF \n 3. SCAN \n 4. C-LOOK \n 5. C-SCAN \n 6. LOOK \n 7. EXIT \n");
    printf("\n\n Enter your choice : ");
    scanf("%d", &choice);
}

void input()
{
    int i;
    printf("Enter Total number of tracks : ");
    scanf("%d", &track);
    printf("Enter total number of disc requests : ");
    scanf("%d", &no_req);
    printf("\nEnter disc requests in FCFS order : ");
    for (i = 0; i < no_req; i++)
    {
        scanf("%d", &disc_req[i]);
    }
    printf("\nEnter current head position : ");
    scanf("%d", &head1);
}

void sstf()
{
    int min, diff;
    int pending = no_req;
    int i, distance = 0, index;
    head = head1;
    for (int i = 0; i < no_req; i++)
    {
        finish[i] = 0;
    }

    printf("\n%d=>", head);
    while (pending > 0)
    {
        min = 999999;
        for (int i = 0; i < no_req; i++)
        {
            diff = abs(head - disc_req[i]);
            if (finish[i] == 0 && diff < min)
            {
                min = diff;
                index = i;
            }
        }
        finish[index] = 1;
        distance += abs(head - disc_req[index]);
        head = disc_req[index];
        pending--;
        printf("%d=>", head);
    }
    printf("End");
    printf("\n \n Total Distance traversed = %d ", distance);
}

void sort()
{
    for (int i = 0; i < no_req; i++)
    {
        for (int j = 0; j < no_req; j++)
        {

            if (disc_req[i] < disc_req[j])
            {
                int temp = disc_req[i];
                disc_req[i] = disc_req[j];
                disc_req[j] = temp;
            }
        }
    }
}
void scan()
{
    int index, dir;
    int i;
    distance = 0;
    head = head1;
    printf("\nEnter the distance of head \n 1 - Towards higher disc(Right) \n 0 - Towards lower disc(left) ");
    scanf("%d", &dir);
    sort();
    printf("\nSorted Disc requests are: ");
    for (int i = 0; i < no_req; i++)
    {
        printf("  %d", disc_req[i]);
    }
    i = 0;
    while (head > disc_req[i])
    {
        index = i;
        i++;
    }
    printf("\nindex=%d", index);
    printf("\n\n%d=>", head);
    if (dir == 1)
    {
        sort();
        for (int i = index + 1; i < no_req; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        distance += abs(head - (track - 1));
        printf("%d=>", track - 1);
        head = track - 1;
        for (int i = index; i >= 0; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    else
    {
        sort();
        for (int i = index; i >= 0; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        distance += abs(head - 0);
        printf("0=>");
        head = 0;
        for (int i = index + 1; i < no_req; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    printf("End");
    printf("\n Total Distance Traversed=%d", distance);
}

void clook()
{
    int index, dir;
    int i;
    distance = 0;
    head = head1;
    printf("\nEnter the direction of head \n 1 - Towards higher disc(right) \n 0 - Towards lower disc(left) ");
    scanf("%d", &dir);
    sort();
    printf("\nSorted Disc requests are: ");
    for (int i = 0; i < no_req; i++)
    {
        printf("  %d", disc_req[i]);
    }
    i = 0;
    while (head >= disc_req[i])
    {
        index = i;
        i++;
    }
    printf("\nindex=%d", index);
    printf("\n\n%d=>", head);
    if (dir == 1)
    {
        sort();
        for (int i = index + 1; i < no_req; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        for (int i = 0; i <= index; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    else
    {
        sort();
        for (int i = index; i >= 0; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        for (int i = no_req; i > index; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    printf("End");
    printf("\n Total Distance Traversed=%d", distance);
}

void cscan()
{
    int index, dir;
    int i;
    distance = 0;
    head = head1;
    printf("\nEnter the distance of head \n 1 - Towards higher disc(Right) \n 0 - Towards lower disc(left) ");
    scanf("%d", &dir);
    sort();
    printf("\nSorted Disc requests are: ");
    for (int i = 0; i < no_req; i++)
    {
        printf("  %d", disc_req[i]);
    }
    i = 0;
    while (head > disc_req[i])
    {
        index = i;
        i++;
    }
    printf("\nindex=%d", index);
    printf("\n\n%d=>", head);
    if (dir == 1)
    {
        sort();
        for (int i = index + 1; i < no_req; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        distance += abs(head - (track - 1));
        printf("%d=>", track - 1);
        head = track - 1;
        distance += abs(head - 0);
        head = 0;
        printf("0=>");
        for (int i = 0; i <= index; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    else
    {
        sort();
        for (int i = index; i >= 0; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        distance += abs(head - 0);
        printf("0=>");
        head = 0;
        distance += abs(head - (track - 1));
        head = track - 1;
        printf("%d=>", track - 1);
        for (int i = no_req; i > index; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    printf("End");
    printf("\n Total Distance Traversed=%d", distance);
}

void look()
{
    int index, dir;
    int i;
    distance = 0;
    head = head1;
    printf("\nEnter the distance of head \n 1 - Towards higher disc(Right) \n 0 - Towards lower disc(left) ");
    scanf("%d", &dir);
    sort();
    printf("\nSorted Disc requests are: ");
    for (int i = 0; i < no_req; i++)
    {
        printf("  %d", disc_req[i]);
    }
    i = 0;
    while (head > disc_req[i])
    {
        index = i;
        i++;
    }
    printf("\nindex=%d", index);
    printf("\n\n%d=>", head);
    if (dir == 1)
    {
        sort();
        for (int i = index + 1; i < no_req; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        for (int i = index; i >= 0; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    else
    {
        sort();
        for (int i = index; i >= 0; i--)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
        for (int i = index + 1; i < no_req; i++)
        {
            printf("%d=>", disc_req[i]);
            distance += abs(head - disc_req[i]);
            head = disc_req[i];
        }
    }
    printf("End");
    printf("\n Total Distance Traversed=%d", distance);
}

int main()
{
    while (1)
    {
        menu();
        switch (choice)
        {
        case 1:
            input();
            break;
        case 2:
            sstf();
            break;
        case 3:
            scan();
            break;
        case 4:
            clook();
            break;
        case 5:
            cscan();
            break;
        case 6:
            look();
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("\nEnter valid choice");
            break;
        }
    }
    return 0;
}