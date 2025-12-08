#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the shared buffer

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0, out = 0;     // Buffer pointers

// Semaphores for synchronization
sem_t empty;    // Counts empty slots in buffer
sem_t full;     // Counts filled slots in buffer
sem_t mutex;    // Mutex for buffer access (binary semaphore)

void print_buffer() {
    printf("Buffer: [");
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(i == in && i == out)
            printf(" IP/OC ");
        else if(i == in)
            printf(" IP ");
        else if(i == out)
            printf(" OC ");
        else if((in > out && i >= out && i < in) || 
                (in < out && (i >= out || i < in)))
            printf(" %d ", buffer[i]);
        else
            printf(" -- ");
        
        if(i < BUFFER_SIZE - 1) printf("|");
    }
    printf("]\n");
}

void* producer(void* arg) {
    int producer_id = *(int*)arg;
    int item;
    
    for(int i = 1; i <= 6; i++) {
        item = producer_id * 100 + i;  // Generate item
        
        printf("\nProducer %d: Trying to produce item %d\n", producer_id, item);
        
        // Wait if buffer is full
        sem_wait(&empty);
        
        // Enter critical section
        sem_wait(&mutex);
        
        // Produce item
        buffer[in] = item;
        printf("Producer %d: PRODUCED item %d at position %d\n", producer_id, item, in);
        in = (in + 1) % BUFFER_SIZE;
        
        print_buffer();
        
        // Exit critical section
        sem_post(&mutex);
        
        // Signal that buffer has one more item
        sem_post(&full);
        
        sleep(rand() % 2 + 1);  // Sleep for 1-2 seconds
    }
    
    printf("\nProducer %d: Finished producing\n", producer_id);
    return NULL;
}

void* consumer(void* arg) {
    int consumer_id = *(int*)arg;
    int item;
    
    for(int i = 1; i <= 4; i++) {
        printf("\nConsumer %d: Trying to consume\n", consumer_id);
        
        // Wait if buffer is empty
        sem_wait(&full);
        
        // Enter critical section
        sem_wait(&mutex);
        
        // Consume item
        item = buffer[out];
        printf("Consumer %d: CONSUMED item %d from position %d\n", consumer_id, item, out);
        buffer[out] = -1;  // Mark as empty
        out = (out + 1) % BUFFER_SIZE;
        
        print_buffer();
        
        // Exit critical section
        sem_post(&mutex);
        
        // Signal that buffer has one empty slot
        sem_post(&empty);
        
        sleep(rand() % 3 + 1);  // Sleep for 1-3 seconds
    }
    
    printf("\nConsumer %d: Finished consuming\n", consumer_id);
    return NULL;
}

int main() {
    pthread_t prod_thread1, prod_thread2, cons_thread1, cons_thread2;
    int prod_id1 = 1, prod_id2 = 2;
    int cons_id1 = 1, cons_id2 = 2;
    
    printf("===========================================\n");
    printf("  PRODUCER-CONSUMER PROBLEM SIMULATION\n");
    printf("===========================================\n\n");
    printf("Legend:\n");
    printf("  IP  = Insertion Point (where producer adds)\n");
    printf("  OC  = Out Point (where consumer takes)\n");
    printf("  ##  = Item in buffer\n");
    printf("  --  = Empty slot\n\n");
    
    // Initialize buffer as empty
    for(int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }
    
    printf("Initial Buffer:\n");
    print_buffer();
    printf("\n");
    
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // All slots are empty initially
    sem_init(&full, 0, 0);             // No slots are full initially
    sem_init(&mutex, 0, 1);            // Binary semaphore for mutual exclusion
    
    // Create producer and consumer threads
    pthread_create(&prod_thread1, NULL, producer, &prod_id1);
    pthread_create(&prod_thread2, NULL, producer, &prod_id2);
    pthread_create(&cons_thread1, NULL, consumer, &cons_id1);
    pthread_create(&cons_thread2, NULL, consumer, &cons_id2);
    
    // Wait for all threads to complete
    pthread_join(prod_thread1, NULL);
    pthread_join(prod_thread2, NULL);
    pthread_join(cons_thread1, NULL);
    pthread_join(cons_thread2, NULL);
    
    printf("\n===========================================\n");
    printf("  SIMULATION COMPLETE\n");
    printf("===========================================\n");
    
    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    return 0;
}
