#include <stdio.h>

int main() {
    int n, i, j, temp;
    int arr[100];
    printf("Enter the number of weeks the cars were sold: ");
    scanf("%d", &n);

    printf("Enter number of cars sold in the %d weeks:\n", n);
    for(i = 0; i < n; i++) {
        printf("Week - %d : ", i+1);
        scanf("%d", &arr[i]);
    }

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    printf("\nThe number of cars sold sorted ascending order are
           : ");
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
