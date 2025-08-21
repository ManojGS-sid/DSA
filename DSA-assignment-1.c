#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tab {
    int pageID;
    char url[100];
    struct Tab *next;
    struct Tab *prev;
} Tab;

Tab *current = NULL;
int idCounter = 1;

Tab* createTab(char *url) {
    Tab *newTab = (Tab*)malloc(sizeof(Tab));
    newTab->pageID = idCounter++;
    strcpy(newTab->url, url);
    newTab->next = NULL;
    newTab->prev = NULL;
    return newTab;
}

void visitNewPage(char *url) {
    Tab *newTab = createTab(url);
    if (current) {
        current->next = newTab;
        newTab->prev = current;
    }
    current = newTab;
    printf("Opened new tab: %s (ID: %d)\n", url, current->pageID);
}

void goForward() {
    if (current && current->next) {
        current = current->next;
        printf("Moved to next tab: %s (ID: %d)\n", current->url, current->pageID);
    } else {
        printf("No forward tab available.\n");
    }
}

void goBack() {
    if (current && current->prev) {
        current = current->prev;
        printf("Moved to previous tab: %s (ID: %d)\n", current->url, current->pageID);
    } else {
        printf("No previous tab available.\n");
    }
}

void showCurrentTab() {
    if (current) {
        printf("Current tab: %s (ID: %d)\n", current->url, current->pageID);
    } else {
        printf("No tab is open.\n");
    }
}

void showHistory(Tab *head) {
    printf("Tab History:\n");
    Tab *temp = head;
    while (temp) {
        printf("ID: %d, URL: %s\n", temp->pageID, temp->url);
        temp = temp->next;
    }
}

void closeCurrentTab() {
    if (!current) {
        printf("No tab to close.\n");
        return;
    }
    printf("Closing tab: %s (ID: %d)\n", current->url, current->pageID);
    Tab *temp = current;

    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;

    if (current->prev) current = current->prev;
    else current = current->next;

    free(temp);
}

int main() {
    int choice;
    char url[100];
    Tab *head = NULL;

    while (1) {
        printf("\n--- Browser Menu ---\n");
        printf("1. Visit a new page\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Show current tab\n");
        printf("5. Close current tab\n");
        printf("6. Show history\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                if (!head) {
                    head = createTab(url);
                    current = head;
                } else {
                    visitNewPage(url);
                }
                break;
            case 2: goBack(); break;
            case 3: goForward(); break;
            case 4: showCurrentTab(); break;
            case 5: closeCurrentTab(); break;
            case 6: showHistory(head); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
