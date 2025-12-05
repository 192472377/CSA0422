#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int shared_data = 0;      // Shared data
int readers_count = 0;    // Count of active readers

sem_t mutex;     // Protects readers_count
sem_t wrt;       // Writer lock

void* reader(void* arg) {
    int id = *(int*)arg;
    
    for(int i = 0; i < 3; i++) {
        // Entry section
        sem_wait(&mutex);
        readers_count++;
        if(readers_count == 1) {
            sem_wait(&wrt);  // First reader locks writers
        }
        sem_post(&mutex);
        
        // Reading section (critical section for readers)
        printf("Reader %d: Reading data = %d\n", id, shared_data);
        sleep(1);  // Simulate reading time
        
        // Exit section
        sem_wait(&mutex);
        readers_count--;
        if(readers_count == 0) {
            sem_post(&wrt);  // Last reader unlocks writers
        }
        sem_post(&mutex);
        
        sleep(1);  // Do other work
    }
    
    printf("Reader %d finished!\n", id);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    
    for(int i = 0; i < 3; i++) {
        // Entry section
        sem_wait(&wrt);  // Writer waits for exclusive access
        
        // Writing section (critical section for writers)
        shared_data++;
        printf("Writer %d: Writing data = %d\n", id, shared_data);
        sleep(2);  // Simulate writing time
        
        // Exit section
        sem_post(&wrt);
        
        sleep(1);  // Do other work
    }
    
    printf("Writer %d finished!\n", id);
    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];
    int r_ids[3] = {1, 2, 3};
    int w_ids[2] = {1, 2};
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    
    printf("=== READER-WRITER PROBLEM SIMULATION ===\n");
    printf("Initial shared data: %d\n\n", shared_data);
    
    // Create reader threads
    for(int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, &r_ids[i]);
    }
    
    // Create writer threads
    for(int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &w_ids[i]);
    }
    
    // Wait for all threads to finish
    for(int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }
    
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    
    printf("\nFinal shared data: %d\n", shared_data);
    printf("Simulation complete!\n");
    
    return 0;
}
