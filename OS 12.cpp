#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

// Philosopher function
void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    
    // Each philosopher tries to eat 3 times
    for (int i = 0; i < 3; i++) {
        printf("Philosopher %d: Thinking...\n", id);
        sleep(1);  // Think for 1 second
        
        // PROBLEM: This can cause deadlock! (All pick left first)
        // printf("Philosopher %d: Picking up left chopstick %d\n", id, left);
        // pthread_mutex_lock(&chopsticks[left]);
        // printf("Philosopher %d: Picking up right chopstick %d\n", id, right);
        // pthread_mutex_lock(&chopsticks[right]);
        
        // SOLUTION: Last philosopher picks up right chopstick first
        if (id == NUM_PHILOSOPHERS - 1) {
            // Last philosopher picks up right chopstick first
            printf("Philosopher %d: Picking up RIGHT chopstick %d first (different order)\n", id, right);
            pthread_mutex_lock(&chopsticks[right]);
            printf("Philosopher %d: Picking up left chopstick %d\n", id, left);
            pthread_mutex_lock(&chopsticks[left]);
        } else {
            // Other philosophers pick up left chopstick first
            printf("Philosopher %d: Picking up LEFT chopstick %d\n", id, left);
            pthread_mutex_lock(&chopsticks[left]);
            printf("Philosopher %d: Picking up right chopstick %d\n", id, right);
            pthread_mutex_lock(&chopsticks[right]);
        }
        
        // Eating
        printf("Philosopher %d: EATING! (Meal %d/3)\n", id, i + 1);
        sleep(2);  // Eat for 2 seconds
        
        // Put down chopsticks
        if (id == NUM_PHILOSOPHERS - 1) {
            pthread_mutex_unlock(&chopsticks[left]);
            pthread_mutex_unlock(&chopsticks[right]);
        } else {
            pthread_mutex_unlock(&chopsticks[right]);
            pthread_mutex_unlock(&chopsticks[left]);
        }
        
        printf("Philosopher %d: Finished eating. Put down chopsticks.\n\n", id);
    }
    
    printf("Philosopher %d: Done with all meals!\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    
    printf("=== DINING PHILOSOPHERS SIMULATION ===\n");
    printf("5 Philosophers, 5 Chopsticks\n");
    printf("Each needs 2 adjacent chopsticks to eat\n\n");
    
    // Initialize chopsticks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }
    
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    
    // Wait for all philosophers to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Clean up
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }
    
    printf("\n=== SIMULATION COMPLETE ===\n");
    printf("All philosophers finished eating without deadlock!\n");
    
    return 0;
}
