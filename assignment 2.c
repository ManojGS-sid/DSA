#include <stdio.h>
#include <string.h>

int main() {
    int m, n;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &m, &n);

    char grid[m][n];
    printf("Enter the grid (only uppercase letters):\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    char word[50];
    printf("Enter the word to search: ");
    scanf("%s", word);

    int word_len = strlen(word);
    int found = 0;

    // Horizontal search (left to right)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n - word_len; j++) {
            int k;
            for (k = 0; k < word_len; k++) {
                if (grid[i][j + k] != word[k])
                    break;
            }
            if (k == word_len) {
                printf("Start: (%d, %d) End: (%d, %d)\n", i, j, i, j + word_len - 1);
                found = 1;
            }
        }
    }

    // Vertical search (top to bottom)
    for (int j = 0; j < n; j++) {
        for (int i = 0; i <= m - word_len; i++) {
            int k;
            for (k = 0; k < word_len; k++) {
                if (grid[i + k][j] != word[k])
                    break;
            }
            if (k == word_len) {
                printf("Start: (%d, %d) End: (%d, %d)\n", i, j, i + word_len - 1, j);
                found = 1;
            }
        }
    }

    if (!found)
        printf("Word not found\n");

    return 0;
}
