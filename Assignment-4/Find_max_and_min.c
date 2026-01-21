#include <stdio.h>

int main() {
    int n, i;
    int water[100];
    int max, min;

    printf("Enter the number of goats in each farm : ");
    scanf("%d", &n);

    printf("Enter the liters of water each of the %d goats drank :\n", n);
    for(i = 0; i < n; i++) {
        printf("Goat - %d : ", i+1);
        scanf("%d", &water[i]);
    }

    max = min = water[0];

    for(i = 1; i < n; i++) {
        if(water[i] > max)
            max = water[i];
        if(water[i] < min)
            min = water[i];
    }

    printf("\nMaximum liters of water is : %d", max);
    printf("\nMinimum liters of water is : %d", min);

    return 0;
}
