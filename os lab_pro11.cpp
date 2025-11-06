#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* threadFunction(void* arg) {
    char* message = (char*)arg;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    char* message1 = "Hello from Thread 1!";
    char* message2 = "Hello from Thread 2!";

    // Create threads
    if (pthread_create(&thread1, NULL, threadFunction, (void*)message1) != 0) {
        perror("Failed to create thread 1");
        exit(1);
    }

    if (pthread_create(&thread2, NULL, threadFunction, (void*)message2) != 0) {
        perror("Failed to create thread 2");
        exit(1);
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

