#include <stdio.h>

int main() {
    int n, i, pos, value;
    int arr[100];

    printf("Enter the number of shelves: ");
    scanf("%d", &n);

    printf("Enter the number of items in each of the %d shelf  in ascending order:\n", n);
    for(i = 0; i < n; i++) {
        printf("Shelf - %d : ", i+1);
        scanf("%d", &arr[i]);
    }

    printf("Enter the missing shelf: ");
    scanf("%d", &value);
    printf("Enter the Position, where the shelf is: ");
    scanf("%d", &pos);

    printf("\nThe current list of the shelves: ");
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    for(i = n; i >= pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos - 1] = value;
    n++;

    printf("\nAfter entering the missing shelf the new list is : ");
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
