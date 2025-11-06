#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep()

sem_t mutex, writeBlock;
int data = 0, readersCount = 0;

void* reader(void* arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1)
            sem_wait(&writeBlock); // First reader blocks writer
        sem_post(&mutex);

        // Reading section
        printf("Reader reads data: %d\n", data);
        sleep(1);

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0)
            sem_post(&writeBlock); // Last reader unblocks writer
        sem_post(&mutex);

        i++;
    }
    return NULL;
}

void* writer(void* arg) {
    int i = 0;
    while (i < 10) {
        sem_wait(&writeBlock);
        // Writing section
        data++;
        printf("Writer writes data: %d\n", data);
        sem_post(&writeBlock);

        sleep(2);
        i++;
    }
    return NULL;
}

int main() {
    pthread_t readers, writers;

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    pthread_create(&readers, NULL, reader, NULL);
    pthread_create(&writers, NULL, writer, NULL);

    pthread_join(readers, NULL);
    pthread_join(writers, NULL);

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}

