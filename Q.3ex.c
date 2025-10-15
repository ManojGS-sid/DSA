#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};


struct Queue {
    struct Node *data[MAX];
    int front, rear;
};


void initQueue(struct Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(struct Queue *q) {
    return q->front == -1;
}

void enqueue(struct Queue *q, struct Node *node) {
    if (q->rear == MAX - 1) return;  // overflow not expected here
    if (q->front == -1) q->front = 0;
    q->data[++q->rear] = node;
}

struct Node* dequeue(struct Queue *q) {
    if (isEmpty(q)) return NULL;
    struct Node *node = q->data[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return node;
}


struct Node* newNode(char ch) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->ch = ch;
    temp->freq = 1;
    temp->left = temp->right = NULL;
    return temp;
}


struct Node* searchChar(struct Node* root, char ch) {
    if (!root) return NULL;
    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        struct Node* temp = dequeue(&q);
        if (temp->ch == ch)
            return temp;
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
    return NULL;
}


void insertLevelWise(struct Node **root, char ch) {
    if (*root == NULL) {
        *root = newNode(ch);
        return;
    }


    struct Node *existing = searchChar(*root, ch);
    if (existing) {
        existing->freq++;
        return;
    }


    struct Queue q;
    initQueue(&q);
    enqueue(&q, *root);

    while (!isEmpty(&q)) {
        struct Node *temp = dequeue(&q);
        if (temp->left == NULL) {
            temp->left = newNode(ch);
            break;
        } else enqueue(&q, temp->left);

        if (temp->right == NULL) {
            temp->right = newNode(ch);
            break;
        } else enqueue(&q, temp->right);
    }
}


struct Node* buildTree(char str[]) {
    struct Node *root = NULL;
    for (int i = 0; i < strlen(str); i++) {
        insertLevelWise(&root, str[i]);
    }
    return root;
}


void levelOrderPrint(struct Node *root) {
    if (!root) return;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        struct Node *temp = dequeue(&q);
        printf("(%c, %d) ", temp->ch, temp->freq);
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
}


int main() {
    char input[100] = "programming";
    struct Node *root = buildTree(input);

    printf("Level Order Traversal with frequencies:\n");
    levelOrderPrint(root);

    return 0;
}
