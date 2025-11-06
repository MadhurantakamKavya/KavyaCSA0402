#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES] = {3, 3, 2}; // Available instances
int maximum[MAX_PROCESSES][MAX_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculate_need() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    for (int i = 0; i < MAX_RESOURCES; i++)
        work[i] = available[i];

    int count = 0;
    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == MAX_RESOURCES) {
                    // This process can finish
                    for (int k = 0; k < MAX_RESOURCES; k++)
                        work[k] += allocation[i][k];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found)
            return 0; // Not safe
    }
    return 1; // Safe state
}

int request_resources(int process_num, int request[]) {
    // Check if request <= need
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process_num][i]) {
            printf("? Error: Process has exceeded its maximum claim.\n");
            return 0;
        }
    }

    // Check if request <= available
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > available[i]) {
            printf("? Resources not available, process must wait.\n");
            return 0;
        }
    }

    // Try to allocate temporarily
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_num][i] += request[i];
        need[process_num][i] -= request[i];
    }

    // Check if safe
    if (is_safe()) {
        return 1; // Request granted
    } else {
        // Roll back
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process_num][i] -= request[i];
            need[process_num][i] += request[i];
        }
        return 0; // Denied
    }
}

int main() {
    int process_num, request[MAX_RESOURCES];

    calculate_need();

    printf("Enter process number (0–4): ");
    scanf("%d", &process_num);

    printf("Enter resource request (e.g., 0 1 0): ");
    for (int i = 0; i < MAX_RESOURCES; i++)
        scanf("%d", &request[i]);

    if (request_resources(process_num, request))
        printf("\n? Request granted. System remains in safe state.\n");
    else
        printf("\n?? Request denied. System would enter unsafe state.\n");

    return 0;
}

