#include <stdio.h>

int main() {
    int n, i, j;
    int marks[100];
    int count;
    printf("Enter the number of students in the class: ");
    scanf("%d", &n);

    printf("Enter the marks for %d students:\n", n);
    for(i = 0; i < n; i++) {
        printf("Student - %d : ", i+1);
        scanf("%d", &marks[i]);
    }
    printf("\nThe unique marks found are: ");
    for(i = 0; i < n; i++) {
        count = 0;
        for(j = 0; j < n; j++) {
            if(marks[i] == marks[j]) {
                count++;
            }
        }
        if(count == 1) {
            printf("%d ", marks[i]);
        }
    }

    return 0;
}
