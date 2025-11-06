#include <stdio.h>

void bestfit(int mp[], int p[], int m, int n) {
    int alloc[20];
    for (int i = 0; i < m; i++)
        alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        int bestIdx = -1;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (bestIdx == -1 || mp[j] < mp[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            alloc[i] = bestIdx;
            mp[bestIdx] -= p[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++) {
        printf("  %d\t\t%d\t\t", i + 1, p[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void firstfit(int mp[], int p[], int m, int n) {
    int alloc[20];
    for (int i = 0; i < m; i++)
        alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                alloc[i] = j;
                mp[j] -= p[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++) {
        printf("  %d\t\t%d\t\t", i + 1, p[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstfit(int mp[], int p[], int m, int n) {
    int alloc[20];
    for (int i = 0; i < m; i++)
        alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        int worstIdx = -1;
        for (int j = 0; j < n; j++) {
            if (mp[j] >= p[i]) {
                if (worstIdx == -1 || mp[j] > mp[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            alloc[i] = worstIdx;
            mp[worstIdx] -= p[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++) {
        printf("  %d\t\t%d\t\t", i + 1, p[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n, mp[20], p[20], ch;
    printf("Enter number of memory partitions: ");
    scanf("%d", &n);
    printf("Enter number of processes: ");
    scanf("%d", &m);

    printf("Enter memory partition sizes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &mp[i]);

    printf("Enter process sizes:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &p[i]);

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            firstfit(mp, p, m, n);
            break;
        case 2:
            bestfit(mp, p, m, n);
            break;
        case 3:
            worstfit(mp, p, m, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

