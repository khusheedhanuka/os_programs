#include <stdio.h>

#define MAX_PROCESSES 100 // Maximum number of processes
#define TIME_QUANTUM 2 // Time quantum

struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
    int remaining_time; // Remaining time
};

struct Process ready_queue[MAX_PROCESSES]; // Array to store the ready queue
int front = 0; // Index of the front element
int rear = -1; // Index of the rear element
int size = 0; // Current size of the ready queue

// Function to check if the ready queue is empty
int is_empty() {
    return (size == 0);
}

// Function to add a process to the ready queue
void enqueue(struct Process p) {
    if (size == MAX_PROCESSES) {
        printf("Ready queue is full\n");
    } else {
        rear = (rear + 1) % MAX_PROCESSES;
        ready_queue[rear] = p;
        size++;
    }
}

// Function to remove a process from the ready queue
struct Process dequeue() {
    if (is_empty()) {
        printf("Ready queue is empty\n");
        struct Process empty_process = {-1, -1, -1, -1}; // Return an empty process
        return empty_process;
    } else {
        struct Process p = ready_queue[front];
        front = (front + 1) % MAX_PROCESSES;
        size--;
        return p;
    }
}

// Function to display the processes in the ready queue
void display() {
    int i;
    printf("Ready queue: ");
    for (i = 0; i < size; i++) {
        printf("P%d ", ready_queue[(front + i) % MAX_PROCESSES].pid);
    }
    printf("\n");
}

int main() {
    // Initialize the processes
    struct Process p1 = {1, 0, 5, 5};
    struct Process p2 = {2, 1, 3, 3};
    struct Process p3 = {3, 2, 1, 1};
    struct Process p4 = {4, 3, 2, 2};

    // Add the processes to the ready queue
    enqueue(p1);
    enqueue(p2);
    enqueue(p3);
    enqueue(p4);

    // Run the scheduling loop
    int time = 0;
    while (!is_empty()) {
        // Get the next process from the ready queue
        struct Process p = dequeue();

        // Run the process for the time quantum
        if (p.remaining_time > TIME_QUANTUM) {
            time += TIME_QUANTUM;
            p.remaining_time -= TIME_QUANTUM;
            printf("Time %d: Running P%d (remaining time = %d)\n", time, p.pid, p.remaining_time);
            enqueue(p); // Add the process back to the ready queue
        } else {
            time += p.remaining_time;
            p.remaining_time = 0;
            printf("Time %d: Finished P%d\n", time, p.pid);
        }
    }

    return 0;
}
