#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 20
#define MAX_RECORD_SIZE 50

typedef struct {
    char data[MAX_RECORD_SIZE];
    int record_number;
} Record;

Record file[MAX_RECORDS];
int total_records = 0;

// Function to add a record sequentially
void addRecord() {
    if(total_records >= MAX_RECORDS) {
        printf("File is full! Cannot add more records.\n");
        return;
    }
    
    char data[MAX_RECORD_SIZE];
    printf("Enter record data: ");
    getchar(); // Clear input buffer
    fgets(data, MAX_RECORD_SIZE, stdin);
    data[strcspn(data, "\n")] = '\0'; // Remove newline
    
    // Add record at the end
    strcpy(file[total_records].data, data);
    file[total_records].record_number = total_records + 1;
    total_records++;
    
    printf("Record added successfully at position %d\n", total_records);
}

// Function to read a specific record (sequential access)
void readRecord(int record_num) {
    if(record_num < 1 || record_num > total_records) {
        printf("Invalid record number!\n");
        return;
    }
    
    printf("\nReading Record %d:\n", record_num);
    printf("You must read all previous records first...\n\n");
    
    // Sequential access: read all previous records
    for(int i = 0; i < record_num; i++) {
        printf("Reading Record %d: %s\n", i+1, file[i].data);
        
        // Small delay to simulate reading time
        for(int j = 0; j < 10000000; j++); // Busy wait for delay
    }
    
    printf("\nFinally reached Record %d: %s\n", record_num, file[record_num-1].data);
}

// Function to display all records
void displayAllRecords() {
    if(total_records == 0) {
        printf("File is empty!\n");
        return;
    }
    
    printf("\n=== ALL RECORDS IN FILE ===\n");
    printf("Position\tRecord Data\n");
    printf("--------\t-----------\n");
    
    for(int i = 0; i < total_records; i++) {
        printf("%d\t\t%s\n", i+1, file[i].data);
    }
    printf("===========================\n");
}

// Function to search for a record (sequential search)
void searchRecord() {
    if(total_records == 0) {
        printf("File is empty!\n");
        return;
    }
    
    char search_data[MAX_RECORD_SIZE];
    printf("Enter data to search: ");
    getchar();
    fgets(search_data, MAX_RECORD_SIZE, stdin);
    search_data[strcspn(search_data, "\n")] = '\0';
    
    printf("\nSequential Search in Progress...\n");
    
    int found = 0;
    for(int i = 0; i < total_records; i++) {
        printf("Checking Record %d: %s\n", i+1, file[i].data);
        
        // Small delay to simulate search time
        for(int j = 0; j < 5000000; j++);
        
        if(strstr(file[i].data, search_data) != NULL) {
            printf("\nFound at Record %d: %s\n", i+1, file[i].data);
            found = 1;
            break; // Can't break in true sequential, but we'll show it
        }
    }
    
    if(!found) {
        printf("\nRecord not found! Searched through all %d records.\n", total_records);
    }
}

// Function to calculate average access time
void calculateAccessTime() {
    if(total_records == 0) {
        printf("File is empty!\n");
        return;
    }
    
    printf("\n=== ACCESS TIME CALCULATION ===\n");
    printf("Assumption: Each record takes 1 unit time to read\n\n");
    
    printf("To access different records:\n");
    printf("Record\tRecords to read\tAccess Time\n");
    printf("------\t---------------\t-----------\n");
    
    for(int i = 1; i <= total_records; i++) {
        printf("%d\t%d\t\t%d units\n", i, i, i);
    }
    
    float avg_time = 0;
    for(int i = 1; i <= total_records; i++) {
        avg_time += i;
    }
    avg_time /= total_records;
    
    printf("\nAverage Access Time: %.2f units\n", avg_time);
    printf("Worst Case (last record): %d units\n", total_records);
    printf("Best Case (first record): 1 unit\n");
}

int main() {
    int choice, record_num;
    
    printf("===== SEQUENTIAL FILE ALLOCATION SIMULATION =====\n");
    printf("Records are stored one after another physically and logically\n");
    printf("To access record N, you must read records 1 through N-1 first\n\n");
    
    // Initialize with some sample records
    strcpy(file[0].data, "Record 1: Employee John");
    file[0].record_number = 1;
    strcpy(file[1].data, "Record 2: Employee Alice");
    file[1].record_number = 2;
    strcpy(file[2].data, "Record 3: Department HR");
    file[2].record_number = 3;
    total_records = 3;
    
    while(1) {
        printf("\n===== MENU =====\n");
        printf("1. Add a new record (at the end)\n");
        printf("2. Read a specific record\n");
        printf("3. Display all records\n");
        printf("4. Search for a record\n");
        printf("5. Calculate access times\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addRecord();
                break;
                
            case 2:
                printf("Enter record number to read (1-%d): ", total_records);
                scanf("%d", &record_num);
                readRecord(record_num);
                break;
                
            case 3:
                displayAllRecords();
                break;
                
            case 4:
                searchRecord();
                break;
                
            case 5:
                calculateAccessTime();
                break;
                
            case 6:
                printf("Exiting program. Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
