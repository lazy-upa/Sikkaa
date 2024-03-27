#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define ENTER 13
#define TAB 9
#define BACKSPACE 8
#define MAX_TRANSACTIONS 100

// Structure to represent a transaction
typedef struct Transaction {
    int current_balance;
    int income;
    int expense;
} Transaction;

void login();
void username();
void add_transaction(int *income, int *expense, int *current_balance, int *food, int *entertainment, int *education, int *others, Transaction history[], int *transaction_count);
void display_history(Transaction history[], int transaction_count);
void save_history(Transaction history[], int transaction_count);

int main() {
    int choice;
    int income = 0, expense = 0, current_balance = 0;
    int food = 0, entertainment = 0, education = 0, others =0;
    Transaction history[MAX_TRANSACTIONS];
    int transaction_count = 0;

    login();

    while (1) {
        system("cls");
        printf("\n\n\nYOUR BALANCE: Rs. %d\n\n\n", current_balance);
        printf("Income: %d \t | Expense: %d\n\n", income, expense);
        add_transaction(&income, &expense, &current_balance, &food, &entertainment, &education, &others, history, &transaction_count);
        printf("\n\n\nYOUR BALANCE: Rs. %d\n\n\n", current_balance);
        printf("Income: %d \t | Expense: %d\n\n", income, expense);
        display_history(history, transaction_count);
        save_history(history, transaction_count);

        printf("\nDo you want to continue? (Press 'y' to continue or any other key to exit)\n");
        char cont;
        scanf(" %c", &cont);
        if (cont != 'y' && cont != 'Y') {
            break;
        }
    }

    return 0;
}

/*-------------------------------------Login Page--------------------------------------------------*/
void login() {
    char xd;
    printf("\t\t\t\t\t----------------Sikka | Personal Finance System--------------------\n");

    printf("\nPress 'y' to continue else Press any other key to exit");
    xd = getch();
    if (xd == 'y' || xd == 'Y') {
        username();
    }
    else {
        printf("We hope to see you again!");
        exit(0); // Exit the program if user chooses not to continue
    }
}

void username() {
    char user[] = {"upahar"};
    char pass[] = {"password"};
    char a[20];
    char ch, pwd[20];
    int c, d, i = 0;
    printf("\n\t\t\t     USERNAME: ");
    scanf("%s", &a);
    printf("\n\t\t\t     PASSWORD: ");
    while((ch = getch()) != ENTER) {
        pwd[i] = ch;
        if(ch == '\b') {
            printf("\b \b");
            if(i > 0) {
                i--;
            }
            continue;
        }
        else {
            printf("*");
            i++;
        }
    }
    pwd[i] = '\0';
    c = strcmp(a, user);
    d = strcmp(pwd, pass);
    if(c != 0 || d != 0) {
        printf("\n\t\t\tinvalid username or password\n");
        login();
    }
}

/*-----------------------------------------Add Transaction------------------------------------------*/
void add_transaction(int *income, int *expense, int *current_balance, int *food, int *entertainment, int *education, int *others, Transaction history[], int *transaction_count) {
    char ch;
    int spend = 0, earn = 0;

    printf("\n\nDo you want to add expense or income? (Enter 'e' for expense & 'i' for income)\n");
    scanf(" %c", &ch);

    if (ch == 'e' || ch == 'E') {
        printf("Enter expense: ");
        scanf("%d", &spend);
        *expense += spend;
        *current_balance -= spend;

        int category;
        printf("Enter category:\n");
        printf("1. Food\n");
        printf("2. Entertainment\n");
        printf("3. Education\n");
        printf("4. Others\n");
        scanf("%d", &category);

        switch (category) {
            case 1:
                *food += spend;
                break;
            case 2:
                *entertainment += spend;
                break;
            case 3:
                *education += spend;
                break;
            case 4:
                *others += spend;
            default:
                printf("Invalid category\n");
                break;
        }
    }
    else if (ch == 'i' || ch == 'I') {
        printf("Enter income: ");
        scanf("%d", &earn);
        *income += earn;
        *current_balance += earn;
    }
    else {
        printf("Invalid input. Please enter 'e' for expense or 'i' for income.");
    }

    // Add transaction to history
    Transaction new_transaction = { *current_balance, *income, *expense };
    history[*transaction_count] = new_transaction;
    (*transaction_count)++;
}

/*----------------------------------Function to display transaction history------------------------------------------*/
void display_history(Transaction history[], int transaction_count) {
    printf("\n\n----- Transaction History -----\n");
    for (int i = 0; i < transaction_count; i++) {
        printf("Transaction %d:\n", i+1);
        printf("Current Balance: Rs. %d\n", history[i].current_balance);
        printf("Income: Rs. %d\n", history[i].income);
        printf("Expense: Rs. %d\n\n", history[i].expense);
    }
}

/*------------------------ Function to save transaction history to a file------------------------------------*/
void save_history(Transaction history[], int transaction_count) {
    FILE *file = fopen("transaction_history.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < transaction_count; i++) {
        fprintf(file, "Transaction %d:\n", i+1);
        fprintf(file, "Current Balance: Rs. %d\n", history[i].current_balance);
        fprintf(file, "Income: Rs. %d\n", history[i].income);
        fprintf(file, "Expense: Rs. %d\n\n", history[i].expense);
    }

    fclose(file);
}

