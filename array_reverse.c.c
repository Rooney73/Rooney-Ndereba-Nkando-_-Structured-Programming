#include <stdio.h>

int main() {
    int numb;
    int i;
    int arr[100];

    printf("Enter the number of units done this semester: ");
    scanf("%d", &numb);

    printf("Enter marks for the %d units done this semester :\n", numb);
    for(i = 0; i < numb; i++) {
        printf("Unit - %d : ", i+1);
        scanf("%d", &arr[i]);
    }
    printf("\nThe marks for the units are : ");
    for(i = 0; i < numb; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nThe marks for the units in reverse are : ");
    for(i = numb - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }

    return 0;
}
