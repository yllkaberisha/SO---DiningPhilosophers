#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *num) {
    int id = *((int *)num);
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        pthread_mutex_lock(&chopsticks[id]);
        pthread_mutex_lock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d is eating.\n", id);
        sleep(3);
        pthread_mutex_unlock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        pthread_mutex_unlock(&chopsticks[id]);
    }
}

int main() {
    int i;
    int nums[NUM_PHILOSOPHERS];
    pthread_t threads[NUM_PHILOSOPHERS];

    // Initialize mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        nums[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &nums[i]);
    }

    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
