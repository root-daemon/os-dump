#include <pthread.h>  // Include the pthread library for multithreading
#include <stdio.h>    // Standard input/output library
#define NUM_THREADS 3

int je, jo, evensum = 0, sumn = 0, oddsum = 0, evenarr[50], oddarr[50];

// Function to find the sum of even numbers
void *Even(void *threadid) {
    int i, n; 
    je = 0;  // Initialize index for even numbers
    n = (int)threadid;  // Get the value of n from the argument

    for (i = 1; i <= n; i++) {
        if (i % 2 == 0) {  // Check if the number is even
            evenarr[je] = i;  // Store even numbers in an array
            evensum = evensum + i;  // Calculate the sum of even numbers
            je++;
        }
    }

    pthread_exit(NULL);  // Terminate the thread
}

// Function to find the sum of odd numbers
void *Odd(void *threadid) {
    int i, n; 
    jo = 0;  // Initialize index for odd numbers
    n = (int)threadid;  // Get the value of n from the argument

    for (i = 1; i <= n; i++) {
        if (i % 2 != 0) {  // Check if the number is odd
            oddarr[jo] = i;  // Store odd numbers in an array
            oddsum = oddsum + i;  // Calculate the sum of odd numbers
            jo++;
        }
    }

    pthread_exit(NULL);  // Terminate the thread
}

// Function to find the sum of natural numbers
void *SumN(void *threadid) {
    int i, n;
    n = (int)threadid;  // Get the value of n from the argument

    for (i = 1; i <= n; i++) {
        sumn = sumn + i;  // Calculate the sum of natural numbers
    }

    pthread_exit(NULL);  // Terminate the thread
}

int main() {
    pthread_t threads[NUM_THREADS];  // Array to hold thread IDs
    int i, t;
    printf("Enter a number\n");
    scanf("%d", &t);

    // Create a thread to call the Even function
    pthread_create(&threads[0], NULL, Even, (void *)t);

    // Create a thread to call the Odd function
    pthread_create(&threads[1], NULL, Odd, (void *)t);

    // Create a thread to call the SumN function
    pthread_create(&threads[2], NULL, SumN, (void *)t);

    // Wait for all threads to complete
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display the results
    printf("The sum of first N natural numbers is %d\n", sumn);
    printf("The sum of first N even numbers is %d\n", evensum);
    printf("The sum of first N odd numbers is %d\n", oddsum);

    printf("The first N Even numbers are:\n");
    for (i = 0; i < je; i++) {
        printf("%d ", evenarr[i]);  // Print all even numbers
    }
    printf("\n");

    printf("The first N Odd numbers are:\n");
    for (i = 0; i < jo; i++) {
        printf("%d ", oddarr[i]);  // Print all odd numbers
    }
    printf("\n");

    pthread_exit(NULL);  // Terminate the main thread
}
