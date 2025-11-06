#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10  // Maximum number of items to be produced/consumed

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

int produced_items = 0, consumed_items = 0;

void* producer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (produced_items >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        sem_wait(&empty);  // wait for empty slot
        pthread_mutex_lock(&mutex);

        // produce item
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] == 0) {
                buffer[i] = produced_items + 1;
                printf("Produced: %d\n", buffer[i]);
                produced_items++;
                break;
            }
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);  // signal full
        Sleep(500);       // 0.5 second
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (consumed_items >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        sem_wait(&full);  // wait for full slot
        pthread_mutex_lock(&mutex);

        // consume item
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] != 0) {
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0;
                consumed_items++;
                break;
            }
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);  // signal empty
        Sleep(800);        // 0.8 second
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize buffer to 0
    for (int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("\nAll items produced and consumed successfully.\n");

    return 0;
}

