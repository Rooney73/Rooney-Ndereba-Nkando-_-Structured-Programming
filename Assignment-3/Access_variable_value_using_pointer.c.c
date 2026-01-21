#include <stdio.h>

int main() {
    int count = 10;
    int *pCount = &count;

    *pCount = 25;

    printf("Updated value of count: %d\n", count);

    return 0;
}
