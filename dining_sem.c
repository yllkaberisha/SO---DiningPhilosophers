#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5 // Number of philosophers
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philosopher_num + N-1) % N
#define RIGHT (philosopher_num + 1) % N

int state[N];
int philosopher_num[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[N];

void test(int philosopher_num) {
    if (state[philosopher_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopher_num] = EATING;
        sleep(1); // Simulate eating
        printf("Philosopher %d takes fork %d and %d\n", philosopher_num + 1, LEFT + 1, philosopher_num + 1);
        printf("Philosopher %d is Eating\n", philosopher_num + 1);
        sem_post(&S[philosopher_num]);
    }
}

void take_fork(int philosopher_num) {
    sem_wait(&mutex);
    state[philosopher_num] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopher_num + 1);
    test(philosopher_num);
    sem_post(&mutex);
    sem_wait(&S[philosopher_num]);
    sleep(1); // Simulate eating
}

void put_fork(int philosopher_num) {
    sem_wait(&mutex);
    state[philosopher_num] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", philosopher_num + 1, LEFT + 1, philosopher_num + 1);
    printf("Philosopher %d is thinking\n", philosopher_num + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1); // Simulate thinking
        take_fork(*i);
        sleep(0); // Simulate eating
        put_fork(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);
    }

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosopher_num[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }
}
