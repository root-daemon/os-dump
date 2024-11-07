#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

/*
This program provides a possible solution for the first readers-writers problem
using a mutex and semaphore. It demonstrates the concept with 10 readers and 5 writers.
You can adjust these numbers as needed.
*/

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int num_readers = 0;

void *writer(void *wno) {
    sem_wait(&wrt);
    cnt *= 2;
    printf("Writer %d modified cnt to %d\n", *((int *)wno), cnt);
    sem_post(&wrt);
}

void *reader(void *rno) {
    // Reader acquires the lock before modifying num_readers
    pthread_mutex_lock(&mutex);
    num_readers++;
    if (num_readers == 1) {
        sem_wait(&wrt); // If this is the first reader, it blocks the writer
    }
    pthread_mutex_unlock(&mutex);

    // Reading Section
    printf("Reader %d: read cnt as %d\n", *((int *)rno), cnt);

    // Reader acquires the lock before modifying num_readers
    pthread_mutex_lock(&mutex);
    num_readers--;
    if (num_readers == 0) {
        sem_post(&wrt); // If this is the last reader, it wakes up the writer
    }
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_t readers[10], writers[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int reader_ids[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int writer_ids[5] = {11, 12, 13, 14, 15};

    for (int i = 0; i < 10; i++) {
        pthread_create(&readers[i], NULL, (void *)reader, (void *)&reader_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&writers[i], NULL, (void *)writer, (void *)&writer_ids[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}