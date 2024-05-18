#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5 // Number of philosophers

// Possible states of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

pthread_mutex_t forks[N];
pthread_cond_t conditions[N];
int states[N]; // States of philosophers

void *philosopher(void *num);
void take_forks(int phil);
void put_forks(int phil);
void test(int phil);

int main() {
    pthread_t thread_id[N];
    int i;

    for (i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&conditions[i], NULL);
        states[i] = THINKING; // Initial state: thinking
    }

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &i);
        sleep(1); // to avoid race conditions in printing
    }

    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    for (i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
        pthread_cond_destroy(&conditions[i]);
    }

    return 0;
}

void *philosopher(void *num) {
    int phil = *(int *)num;

    while (1) {
        sleep(2); // Thinking for 2 seconds
        printf("Philosopher %d is thinking.\n", phil);
        take_forks(phil); // Take forks to eat
        sleep(2); // Eating for 2 seconds
        printf("Philosopher %d is eating.\n", phil);
        put_forks(phil); // Put forks after eating
        printf("Philosopher %d has finished eating.\n", phil);
    }
}

void take_forks(int phil) {
    pthread_mutex_lock(&forks[phil]);
    states[phil] = HUNGRY; // Change state to hungry
    printf("Philosopher %d is hungry and trying to take forks.\n", phil);
    test(phil); // Test if philosopher can eat
    while (states[phil] != EATING) { // While not eating
        pthread_cond_wait(&conditions[phil], &forks[phil]); // Wait for signal
    }
    pthread_mutex_unlock(&forks[phil]);
}

void put_forks(int phil) {
    pthread_mutex_lock(&forks[phil]);
    states[phil] = THINKING; // Change state to thinking
    printf("Philosopher %d has has put down forks.\n", phil);
    test((phil + N - 1) % N); // Test left neighbor
    test((phil + 1) % N); // Test right neighbor
    pthread_mutex_unlock(&forks[phil]);
}

void test(int phil) {
    if (states[phil] == HUNGRY && states[(phil + N - 1) % N] != EATING && states[(phil + 1) % N] != EATING) {
        states[phil] = EATING; // Change state to eating
        printf("Philosopher %d has taken forks.\n", phil);
        pthread_cond_signal(&conditions[phil]); // Signal that this philosopher can eat
    }
}
