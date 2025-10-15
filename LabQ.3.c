#include <stdio.h>
#include <string.h>

#define MAX 10

// Stacks for undo and redo
char undoStack[MAX][50];
char redoStack[MAX][50];
int topUndo = -1;
int topRedo = -1;

// Push function
void push(char stack[MAX][50], int *top, char operation[]) {
    if (*top >= MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    strcpy(stack[++(*top)], operation);
}

// Pop function
void pop(char stack[MAX][50], int *top, char operation[]) {
    if (*top < 0) {
        strcpy(operation, "NULL");
        return;
    }
    strcpy(operation, stack[(*top)--]);
}

// Perform operation (Push to undo stack, clear redo stack)
void performOperation(char operation[]) {
    // Push the operation to undo stack
    push(undoStack, &topUndo, operation);

    // Clear redo stack
    topRedo = -1;

    printf("Performed operation: \"%s\"\n", operation);
    if (topUndo >= 0)
        printf("Next Operation that can be undone is = \"%s\"\n", undoStack[topUndo]);
    printf("\n");
}

// Undo operation
void undoOperation() {
    char operation[50];
    if (topUndo < 0) {
        printf("Nothing to undo.\n\n");
        return;
    }

    // Pop from undo and push to redo
    pop(undoStack, &topUndo, operation);
    push(redoStack, &topRedo, operation);

    printf("Undone. Next Operation that can be undone is = ");
    if (topUndo >= 0)
        printf("\"%s\"\n", undoStack[topUndo]);
    else
        printf("None\n");
    printf("\n");
}

// Redo operation
void redoOperation() {
    char operation[50];
    if (topRedo < 0) {
        printf("Nothing to redo.\n\n");
        return;
    }

    // Pop from redo and push back to undo
    pop(redoStack, &topRedo, operation);
    push(undoStack, &topUndo, operation);

    printf("Redo completed. Next Operation that can be redone is = ");
    if (topRedo >= 0)
        printf("\"%s\"\n", redoStack[topRedo]);
    else
        printf("None\n");
    printf("\n");
}

int main() {
    performOperation("op1");
    performOperation("op2");
    performOperation("op3");
    undoOperation();
    undoOperation();
    redoOperation();
    performOperation("op4");
    undoOperation();

    return 0;
}
