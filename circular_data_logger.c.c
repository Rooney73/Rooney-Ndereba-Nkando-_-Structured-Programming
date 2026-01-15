#include <stdio.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int head = 0;
int count = 0;

void insertSample(int value) {
    buffer[head] = value;
    head = (head + 1) % BUFFER_SIZE;

    if (count < BUFFER_SIZE) {
        count++;
    }
}

void printSamples() {
    int i;
    int index;

    printf("Stored samples (oldest → newest): ");

    index = (head - count + BUFFER_SIZE) % BUFFER_SIZE;

    for (i = 0; i < count; i++) {
        printf("%d ", buffer[index]);
        index = (index + 1) % BUFFER_SIZE;
    }
    printf("\n");
}

int main() {
    int value;
    char choice;

    printf("Circular Data Logger (Buffer Size = %d)\n", BUFFER_SIZE);

    do {
        printf("Enter sensor value: ");
        scanf("%d", &value);

        insertSample(value);

        printf("Do you want to enter another value? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printSamples();

    return 0;
}
