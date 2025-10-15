#include <stdio.h>
#include <string.h>

#define DAYS 30


struct Member {
    char name[50];
    int steps[DAYS];
};


void analyzeSteps(struct Member members[], int n) {
    for (int i = 0; i < n; i++) {
        int countOver10k = 0;
        int maxSteps = members[i].steps[0];

        for (int j = 0; j < DAYS; j++) {
            if (members[i].steps[j] > 10000)
                countOver10k++;
            if (members[i].steps[j] > maxSteps)
                maxSteps = members[i].steps[j];
        }

        printf("\nMember: %s\n", members[i].name);
        printf("Days over 10,000 steps: %d\n", countOver10k);
        printf("Maximum steps in a day: %d\n", maxSteps);
    }
}


int main() {
    int n = 2;
    struct Member members[2] = {
        {"Alice", {12000, 11000, 8000, 5000, 10200, 9700, 10800, 9500, 8700, 12000,
                   10000, 15000, 8900, 9000, 10400, 11000, 10050, 7800, 11500, 10200,
                   11100, 9500, 9700, 8600, 10800, 10020, 10500, 9800, 9700, 9500}},
        {"Bob", {8000, 9500, 7000, 6500, 8700, 9000, 9100, 8800, 9400, 9700,
                 9600, 9800, 9200, 8800, 9700, 9400, 9100, 9300, 8900, 8500,
                 8700, 9100, 8900, 8800, 9400, 9500, 9700, 9600, 9100, 9000}}
    };

    analyzeSteps(members, n);
    return 0;
}
