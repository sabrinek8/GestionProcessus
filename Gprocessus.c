#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

#define NUM_CHILDREN 4

sem_t *sem_start;

void child_task(int child_num) {
    printf("Child %d waiting for start signal\n", child_num);
    sem_wait(sem_start);  // Wait for the start signal

    printf("Child %d received start signal\n", child_num);

    // Simulate complex task
    printf("Child %d is performing task\n", child_num);
    sleep(2);  // Simulate a task with sleep
    for (volatile int i = 0; i < 1000000; i++);  // Simulate computation

    // Send confirmation signal to parent
    kill(getppid(), SIGUSR2);
    printf("Child %d sent confirmation signal\n", child_num);
    exit(0);
}

void handle_sigusr1(int sig) {
    // Placeholder for handling SIGUSR1 in children
}

void handle_sigusr2(int sig) {
    // Placeholder for handling SIGUSR2 in parent
    printf("Parent received confirmation signal from a child\n");
}

int main() {
    pid_t pids[NUM_CHILDREN];
    int i;

    // Set up signal handlers
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    // Initialize semaphore
    sem_start = sem_open("/sem_start", O_CREAT, 0644, 0);
    if (sem_start == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Create child processes
    for (i = 0; i < NUM_CHILDREN; i++) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            // In child process
            child_task(i + 1);
        }
    }

    // Give time for all children to be ready
    sleep(1);

    // Send SIGUSR1 signal to all children to start tasks
    for (i = 0; i < NUM_CHILDREN; i++) {
        kill(pids[i], SIGUSR1);
        sem_post(sem_start);  // Post the semaphore for each child
    }

    // Wait for all child processes to complete
    for (i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    // Clean up semaphore
    sem_close(sem_start);
    sem_unlink("/sem_start");

    printf("Parent: All children have completed their tasks.\n");
    return 0;
}
