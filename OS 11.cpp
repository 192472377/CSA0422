#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Function that will be executed by each thread
void* print_numbers(void* arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 1; i <= 5; i++) {
        printf("Thread %d: Count %d\n", thread_id, i);
        sleep(1);  // Simulate some work
    }
    
    printf("Thread %d finished!\n", thread_id);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;
    
    printf("Main thread: Creating threads...\n");
    
    // Create two threads
    pthread_create(&thread1, NULL, print_numbers, &id1);
    pthread_create(&thread2, NULL, print_numbers, &id2);
    
    printf("Main thread: Threads created. Waiting for them to finish...\n");
    
    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Main thread: All threads completed!\n");
    return 0;
}
