#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty;    // Counts empty slots
sem_t full;     // Counts filled slots
pthread_mutex_t mutex;  // Protects buffer access

void* producer(void* arg) {
    int item;
    
    for(int i = 1; i <= 10; i++) {
        item = i;  // Produce item
        
        // Wait for empty slot
        sem_wait(&empty);
        
        // Enter critical section
        pthread_mutex_lock(&mutex);
        
        buffer[in] = item;
        printf("Producer produced: %d (at position %d)\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        
        // Exit critical section
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer has new item
        sem_post(&full);
        
        sleep(1);  // Simulate production time
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    
    for(int i = 1; i <= 10; i++) {
        // Wait for full slot
        sem_wait(&full);
        
        // Enter critical section
        pthread_mutex_lock(&mutex);
        
        item = buffer[out];
        printf("Consumer consumed: %d (from position %d)\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        
        // Exit critical section
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer has empty slot
        sem_post(&empty);
        
        sleep(2);  // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // All slots empty initially
    sem_init(&full, 0, 0);             // No slots full initially
    pthread_mutex_init(&mutex, NULL);
    
    // Display buffer state
    printf("Buffer size: %d\n", BUFFER_SIZE);
    printf("Starting Producer-Consumer simulation...\n\n");
    
    // Create threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    
    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    
    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    printf("\nSimulation complete!\n");
    return 0;
}
