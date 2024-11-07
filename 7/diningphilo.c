#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];   

void *philosopher(void *num) {
    int id = *(int *)num;
    

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);  
        
        printf("Philosopher %d is hungry.\n", id);
        
        // Pick up forks: left and right
        sem_wait(&forks[id]);             // Pick up left fork
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork
        
        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1);  // Simulate eating

        // Put down forks: left and right
        sem_post(&forks[id]);             // Put down left fork
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);  // Put down right fork
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
         sem_init(&forks[i], 0, 1);  // Each fork is initially available
    }
    
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    
    // Wait for all philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    
    return 0;
}
