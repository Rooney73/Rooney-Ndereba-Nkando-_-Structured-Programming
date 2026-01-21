#include <stdio.h>

void incrementByValue(int x) {
    x++;
}

void incrementByReference(int *x) {
    (*x)++;
}

int main() {
    int num = 10;

    incrementByValue(num);
    printf("After pass by value: %d\n", num);

    incrementByReference(&num);
    printf("After pass by reference: %d\n", num);

    return 0;
}
