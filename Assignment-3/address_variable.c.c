#include <stdio.h>

int main() {

    int num = 10;
    int *ptr;
    ptr = &num;

    printf(" Task 2: Display Address of a Variable \n\n");
    printf("Value of num: %d\n", num);
    printf("Value stored in ptr (address of num): %p\n",ptr);
    printf("Address of num: %p\n",&num);
    printf("Value accessed using *ptr (dereferenced): %d\n", *ptr);

    return 0;
}
