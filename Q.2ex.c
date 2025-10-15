#include <stdio.h>
#include <stdlib.h>


struct Node {
    int songID;
    struct Node *next;
};


struct Node* newNode(int id) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->songID = id;
    temp->next = NULL;
    return temp;
}


struct Node* reversePlaylistSegment(struct Node* head, int m, int n) {
    if (!head || m == n)
        return head;

    struct Node dummy;
    dummy.next = head;
    struct Node* prev = &dummy;


    for (int i = 1; i < m; i++)
        prev = prev->next;

    struct Node* curr = prev->next;
    struct Node* nextNode = NULL;


    for (int i = 0; i < n - m; i++) {
        nextNode = curr->next;
        curr->next = nextNode->next;
        nextNode->next = prev->next;
        prev->next = nextNode;
    }

    return dummy.next;
}


void printPlaylist(struct Node* head) {
    while (head) {
        printf("%d", head->songID);
        if (head->next)
            printf(" -> ");
        head = head->next;
    }
    printf("\n");
}


int main() {

    struct Node* head = newNode(101);
    head->next = newNode(102);
    head->next->next = newNode(103);
    head->next->next->next = newNode(104);
    head->next->next->next->next = newNode(105);
    head->next->next->next->next->next = newNode(106);
    head->next->next->next->next->next->next = newNode(107);

    printf("Original playlist:\n");
    printPlaylist(head);

    int m = 2, n = 5;
    head = reversePlaylistSegment(head, m, n);

    printf("\nModified playlist:\n");
    printPlaylist(head);

    return 0;
}
