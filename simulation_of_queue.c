#include <stdio.h>
#include <stdlib.h>

// Structure for glass
struct glass {
    int data;
    struct glass* next;
};

// Structure for stack
struct stack {
    struct glass* bottom;
    struct glass* top;
};

// Structure for queue
struct queue {
    struct stack* stack1;
    struct stack* stack2;
};

// Function to create a new glass
struct glass* createGlass(int data) {
    struct glass* newGlass = (struct glass*)malloc(sizeof(struct glass));
    newGlass->data = data;
    newGlass->next = NULL;
    return newGlass;
}

// Function to create a new stack
struct stack* createStack() {
    struct stack* newStack = (struct stack*)malloc(sizeof(struct stack));
    newStack->bottom = NULL;
    newStack->top = NULL;
    return newStack;
}

// Function to create a new queue
struct queue* createQueue() {
    struct queue* newQueue = (struct queue*)malloc(sizeof(struct queue));
    newQueue->stack1 = createStack();
    newQueue->stack2 = createStack();
    return newQueue;
}

// Function to enqueue an element
void enqueue(struct queue* q, int data) {
    while (q->stack1->top != NULL) {
        q->stack2->bottom = q->stack1->top;
        q->stack1->top = q->stack1->top->next;
        q->stack2->bottom->next = q->stack2->top;
        q->stack2->top = q->stack2->bottom;
    }

    q->stack1->bottom = createGlass(data);
    q->stack1->bottom->next = q->stack2->top;
    q->stack2->top = q->stack1->bottom;

    while (q->stack2->top != NULL) {
        q->stack1->bottom = q->stack2->top;
        q->stack2->top = q->stack2->top->next;
        q->stack1->bottom->next = q->stack1->top;
        q->stack1->top = q->stack1->bottom;
    }
}

// Function to dequeue an element
int dequeue(struct queue* q) {
    if (q->stack1->top == NULL) {
        printf("Queue is empty.\n");
        return -1;
    }

    int data = q->stack1->top->data;
    q->stack1->bottom = q->stack1->top;
    q->stack1->top = q->stack1->top->next;
    free(q->stack1->bottom);
    return data;
}

// Function to display the queue
void display(struct queue* q) {
    if (q->stack1->top == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct glass* temp = q->stack1->top;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct queue* q = createQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 130);
    enqueue(q, 203);
    enqueue(q, 303);
    enqueue(q, 110);
    enqueue(q, 202);
    enqueue(q, 310);

    display(q); // Output: Queue: 10 20 30

    printf("Dequeued element: %d\n", dequeue(q)); // Output: Dequeued element: 10
    printf("Dequeued element: %d\n", dequeue(q));
    printf("Dequeued element: %d\n", dequeue(q));

    display(q); // Output: Queue: 20 30

    return 0;
}

