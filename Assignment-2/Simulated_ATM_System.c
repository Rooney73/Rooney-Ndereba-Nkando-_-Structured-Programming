#include <stdio.h>

/* Function declarations */
int login(void);
void showMenu(void);
void checkBalance(float balance);
float deposit(float balance);
float withdrawMoney(float balance);

int main(void) {
    float balance = 5500.0;
    int choice;

    if (!login()) {
        return 0;
    }

    do {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;

            case 2:
                balance = deposit(balance);
                break;

            case 3:
                balance = withdrawMoney(balance);
                break;

            case 4:
                printf("Thank you for using the ATM.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    return 0;
}

/* Function definitions */

int login(void) {
    int pin = 7567;
    int enteredPin;
    int attempts = 3;

    while (attempts > 0) {
        printf("Enter PIN: ");
        scanf("%d", &enteredPin);

        if (enteredPin == pin) {
            printf("Login successful!\n");
            return 1;
        } else {
            attempts--;
            printf("Wrong PIN. Attempts left: %d\n", attempts);
        }
    }

    printf("Access denied.\n");
    return 0;
}

void showMenu(void) {
    printf("\n--- ATM MENU ---\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Exit\n");
}

void checkBalance(float balance) {
    printf("Current balance: %.2f\n", balance);
}

float deposit(float balance) {
    float amount;

    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    if (amount > 0) {
        balance += amount;
        printf("New balance: %.2f\n", balance);
    } else {
        printf("Invalid amount.\n");
    }

    return balance;
}

float withdrawMoney(float balance) {
    float amount;

    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
    } else if (amount > balance) {
        printf("Insufficient balance.\n");
    } else {
        balance -= amount;
        printf("New balance: %.2f\n", balance);
    }

    return balance;
}
