#include <stdio.h>
#include <string.h>
#include <conio.h> 

struct User {
    char phone[50];
    char accountNumber[50];
    char password[50];
    float balance;
};

int main() {
    struct User users[10];
    int userCount = 0;
    int loggedInUser = -1; // Index of the logged-in user
    int i, choice;
    char ch; // To store characters temporarily

    printf("Welcome to C Banking!\n");

    do {
        printf("\nSelect an option:\n1. Register an account\n2. Login to account\n3. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1 && userCount < 10) { // Register an account
            struct User newUser;

            // User input
            printf("Enter your account number: ");
            scanf("%s", newUser.accountNumber);
            printf("Enter your phone number: ");
            scanf("%s", newUser.phone);
            printf("Create a password: ");

            // Input password without displaying characters
            i = 0;
            while ((ch = getch()) != '\r' && i < sizeof(newUser.password) - 1) {
                if (ch == 8 && i > 0) { // Handle backspace
                    printf("\b \b");
                    newUser.password[--i] = '\0';
                } else {
                    newUser.password[i++] = ch;
                    putchar('*');
                }
            }
            newUser.password[i] = '\0';
            printf("\n");

            newUser.balance = 0;
            users[userCount++] = newUser; // Store the new user
            printf("Account successfully registered.\n");
        } else if (choice == 2) { // Login
            char phone[50], password[50];
            printf("Enter your phone number: ");
            scanf("%s", phone);
            printf("Enter your password: ");

            i = 0;
            while ((ch = getch()) != '\r' && i < sizeof(password) - 1) {
                if (ch == 8 && i > 0) { // Handle backspace
                    printf("\b \b");
                    password[--i] = '\0';
                } else {
                    password[i++] = ch;
                    putchar('*');
                }
            }
            password[i] = '\0';
            printf("\n");

            // Find the matching user
            for (i = 0; i < userCount; i++) {
                if (strcmp(phone, users[i].phone) == 0 && strcmp(password, users[i].password) == 0) {
                    printf("Welcome, %s!\n", users[i].phone);
                    loggedInUser = i; // Set the index of the logged-in user
                    break;
                }
            }

            // Display login status
            if (loggedInUser == -1) {
                printf("Login failed. Please check your phone number and password.\n");
            }
        } else if (choice == 3) { // Exit
            printf("Thank you for using our banking system!\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }

        // Display user-specific menu if logged in
        if (loggedInUser != -1) {
            while (1) {
                printf("\nSelect an option:\n1. Check balance\n2. Deposit money\n3. Withdraw money\n");
                printf("4. Transfer money\n5. Exit\nYour choice: ");
                scanf("%d", &choice);

                // Perform user actions
                if (choice == 5) { // Exit user menu
                    printf("Thank you for using our banking system!\n");
                    break;
                } else if (choice == 1) { // Check balance
                    printf("Your current balance is Rs.%.2f\n", users[loggedInUser].balance);
                } else if (choice == 2) { // Deposit money
                    float amount;
                    printf("Enter the amount to deposit: ");
                    scanf("%f", &amount);
                    users[loggedInUser].balance += amount;
                    printf("Amount deposited successfully.\n");
                } else if (choice == 3) { // Withdraw money
                    float amount;
                    printf("Enter the amount to withdraw: ");
                    scanf("%f", &amount);
                    if (amount <= users[loggedInUser].balance) {
                        users[loggedInUser].balance -= amount;
                        printf("Amount withdrawn successfully.\n");
                    } else {
                        printf("Insufficient balance.\n");
                    }
                } else if (choice == 4) { // Transfer money
                    char recipientPhone[50];
                    printf("Enter recipient's phone number: ");
                    scanf("%s", recipientPhone);
                    int recipientIndex = -1;

                    // Find the recipient's user index
                    for (i = 0; i < userCount; i++) {
                        if (strcmp(recipientPhone, users[i].phone) == 0) {
                            recipientIndex = i;
                            break;
                        }
                    }

                    if (recipientIndex != -1) {
                        float amount;
                        printf("Enter the amount to transfer: ");
                        scanf("%f", &amount);

                        if (amount <= users[loggedInUser].balance) {
                            users[loggedInUser].balance -= amount;
                            users[recipientIndex].balance += amount;
                            printf("Amount transferred successfully.\n");
                        } else {
                            printf("Insufficient balance for transfer.\n");
                        }
                    } else {
                        printf("Recipient's phone number is not registered.\n");
                    }
                } else {
                    printf("Invalid choice. Please try again.\n");
                }
            }
            loggedInUser = -1; // Reset logged-in status after user menu
        }

    } while (choice != 3); // Exit main loop when user chooses to exit

    return 0; // Return 0 to indicate successful program execution
}

