#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// Structure for glass
struct glass {
    char glassColor[MAX];
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
struct glass* createGlass(char glassColor[MAX]) {
    struct glass* newGlass = (struct glass*)malloc(sizeof(struct glass));
    if(newGlass == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newGlass->glassColor, glassColor);
    newGlass->next = NULL;
    return newGlass;
}

// Function to create a new stack
struct stack* createStack() {
    struct stack* newStack = (struct stack*)malloc(sizeof(struct stack));
    if(newStack == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newStack->bottom = NULL;
    newStack->top = NULL;
    return newStack;
}

// Function to create a new queue
struct queue* createQueue() {
    struct queue* newQueue = (struct queue*)malloc(sizeof(struct queue));
    if(newQueue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newQueue->stack1 = createStack();
    newQueue->stack2 = createStack();
    return newQueue;
}

// Function to enqueue an element
void enqueue(struct queue* q, char glassColor[MAX]) {
    while (q->stack1->top != NULL) {
        q->stack2->bottom = q->stack1->top;
        q->stack1->top = q->stack1->top->next;
        q->stack2->bottom->next = q->stack2->top;
        q->stack2->top = q->stack2->bottom;
    }

    q->stack1->bottom = createGlass(glassColor);
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
void dequeue(struct queue* q) {
    if (q->stack1->top == NULL) {
        printf("there are no glasses.\n");
        exit(1);
    }

    char tmp[MAX];
    strcpy(tmp, q->stack1->top->glassColor);
    q->stack1->bottom = q->stack1->top;
    q->stack1->top = q->stack1->top->next;
    free(q->stack1->bottom);
    printf("%s color glass is removed...\n", tmp);
}

// Function to display the queue
void display(struct queue* q) {
    int numOfGlass = 0;
    if (q->stack1->top == NULL) {
        printf("there are no glasses.\n");
        return;
    }

    struct glass* temp = q->stack1->top;
    printf("\ncolor of glasses are sequentially: ");
    while (temp != NULL) {
        printf("%s ", temp->glassColor);
        temp = temp->next;
        numOfGlass++;
    }
    printf("\n");
    printf("Total number of glasses: %d\n\n", numOfGlass);
}

int main() {
    struct queue* q = createQueue();

    enqueue(q, "red");
    enqueue(q, "green");
    enqueue(q, "blue");
    enqueue(q, "yellow");
    enqueue(q, "violet");
    enqueue(q, "black");
    enqueue(q, "white");
    enqueue(q, "indigo");
    enqueue(q, "gray");

    display(q);

    dequeue(q);
    dequeue(q);
    dequeue(q);

    display(q);

    return 0;
}

