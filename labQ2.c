#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int capacity;
    int front;
    int rear;
    int count;
} CircularQueue;

CircularQueue *createQueue(int capacity) {
    CircularQueue *q = (CircularQueue *)malloc(sizeof(CircularQueue));
    q->data = (int *)malloc(sizeof(int) * capacity);
    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    return q;
}

int isFull(CircularQueue *q) {
    return q->count == q->capacity;
}

int isEmpty(CircularQueue *q) {
    return q->count == 0;
}

void enqueue(CircularQueue *q, int customerID) {
    if (isFull(q)) {
        printf("Queue is full. Cannot add call: %d\n", customerID);
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = customerID;
    q->count++;
    printf("Call added: %d\n", customerID);
}

int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Nothing to remove.\n");
        return -1; // indicates empty
    }
    int val = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->count--;
    if (q->count == 0) {
        q->front = 0;
        q->rear = -1;
    }
    return val;
}

void displayQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents: ");
    int i = q->front;
    for (int c = 0; c < q->count; ++c) {
        printf("%d ", q->data[i]);
        i = (i + 1) % q->capacity;
    }
    printf("\n");
}

void freeQueue(CircularQueue *q) {
    free(q->data);
    free(q);
}


int main() {
    int capacity = 5;
    CircularQueue *q = createQueue(capacity);

    enqueue(q, 101);
    enqueue(q, 102);
    enqueue(q, 103);
    enqueue(q, 104);
    enqueue(q, 105);

    enqueue(q, 106);

    displayQueue(q);


    int removed = dequeue(q);
    if (removed != -1) printf("Call removed (served): %d\n", removed);


    enqueue(q, 107);

    displayQueue(q);

    freeQueue(q);
    return 0;
}
