#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

void *fun1();
void *fun2();

int shared = 1; // Shared variable
sem_t s; // Semaphore variable

int main() {
    sem_init(&s, 0, 1); // Initialize semaphore variable

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    sleep(1);
    pthread_create(&thread2, NULL, fun2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared is %d\n", shared);
}

void *fun1() {
    int x;

    sem_wait(&s); // Executes wait operation on s
    x = shared; // Thread1 reads value of shared variable
    printf("Thread1 reads the value as %d\n", x);

    x++; // Thread1 increments its value
    printf("Local updation by Thread1: %d\n", x);

    sleep(1); // Thread1 is preempted by thread 2

    shared = x; // Thread1 updates the value of shared variable
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);

    sem_post(&s);
}

void *fun2() {
    int y;

    sem_wait(&s);
    y = shared; // Thread2 reads value of shared variable
    printf("Thread2 reads the value as %d\n", y);

    y--; // Thread2 decrements its value
    printf("Local updation by Thread2: %d\n", y);

    sleep(1); // Thread2 is preempted by thread 1

    shared = y; // Thread2 updates the value of shared variable
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);

    sem_post(&s);
}
/*
OUTPUT:
Thread1 reads the value as 1
Local updation by Thread1: 2
Thread2 reads the value as 1
Local updation by Thread2: 0
Value of shared variable updated by Thread1 is: 2
Value of shared variable updated by Thread2 is: 0
Final value of shared is 0
*/