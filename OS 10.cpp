#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Message {
    int type;
    char text[100];
};

struct Message queue[10];
int front = 0, rear = 0;

void send_message() {
    if(rear >= 10) {
        printf("Queue full!\n");
        return;
    }
    
    printf("Enter message: ");
    scanf(" %[^\n]", queue[rear].text);
    queue[rear].type = 1;
    rear++;
    printf("Message sent to queue!\n");
}

void receive_message() {
    if(front >= rear) {
        printf("No messages in queue!\n");
        return;
    }
    
    printf("Message received: %s\n", queue[front].text);
    front++;
}

void display_queue() {
    printf("\n=== MESSAGE QUEUE ===\n");
    if(front >= rear) {
        printf("Queue is empty!\n");
        return;
    }
    
    for(int i = front; i < rear; i++) {
        printf("[%d] %s\n", i, queue[i].text);
    }
}

int main() {
    int choice;
    
    while(1) {
        printf("\n1. Send Message\n");
        printf("2. Receive Message\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: send_message(); break;
            case 2: receive_message(); break;
            case 3: display_queue(); break;
            case 4: 
                printf("Exiting...\n");
                return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
