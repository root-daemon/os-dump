#include <stdio.h>
#include <unistd.h>

int main() {
    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Error in fork
        printf("Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("In Child Process\n");
        printf("Parent Process ID: %d\n", getppid());  // Get parent process ID
        printf("Child Process ID: %d\n", getpid());    // Get child process ID
    } else {
        // Parent process
        sleep(1);  // Ensure the child process runs first
        printf("In Parent Process\n");
        printf("Parent Process ID: %d\n", getpid());   // Get parent process ID
        printf("Child Process ID: %d\n", pid);         // The 'pid' returned by fork() in the parent process is the child process ID
    }

    return 0;
}
