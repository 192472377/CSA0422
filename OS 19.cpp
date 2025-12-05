#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared_counter = 0;  // Shared resource
pthread_mutex_t lock;    // Mutex lock

void* increment_counter(void* arg) {
    int thread_id = *(int*)arg;
    
    for(int i = 0; i < 5; i++) {
        // Lock before accessing shared resource
        pthread_mutex_lock(&lock);
        
        // Critical section starts
        int current = shared_counter;
        printf("Thread %d: Read counter = %d\n", thread_id, current);
        sleep(1);  // Simulate some processing time
        
        shared_counter = current + 1;
        printf("Thread %d: Updated counter to = %d\n", thread_id, shared_counter);
        // Critical section ends
        
        // Unlock after finishing
        pthread_mutex_unlock(&lock);
        
        sleep(1);  // Do some non-critical work
    }
    
    printf("Thread %d finished!\n", thread_id);
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;
    int id1 = 1, id2 = 2, id3 = 3;
    
    // Initialize mutex
    pthread_mutex_init(&lock, NULL);
    
    printf("Initial counter value: %d\n", shared_counter);
    printf("Starting 3 threads to increment counter...\n\n");
    
    // Create threads
    pthread_create(&thread1, NULL, increment_counter, &id1);
    pthread_create(&thread2, NULL, increment_counter, &id2);
    pthread_create(&thread3, NULL, increment_counter, &id3);
    
    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    // Destroy mutex
    pthread_mutex_destroy(&lock);
    
    printf("\nFinal counter value: %d\n", shared_counter);
    printf("Expected value: 15 (3 threads × 5 increments each)\n");
    
    return 0;
}
