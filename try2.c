#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRANSACTIONS 100

// Structure to represent a transaction
typedef struct History {
    int amount;
    char transaction_type; // 'e' for expense, 'i' for income
    char transaction_detail[20]; // Detail of the transaction (e.g., category)
} History;

void login();
void add_transaction(int *income, int *expense, int *current_balance, History history[], int *history_count);
void display_history(History history[], int history_count);
void save_history(History history[], int history_count);

int main() {
    int income = 0, expense = 0, current_balance = 0;
    History history[MAX_TRANSACTIONS];
    int history_count = 0;

    login();

    while (1) {
        system("cls");
        printf("\n\n\nYOUR BALANCE: Rs. %d\n\n\n", current_balance);
        printf("Income: %d \t | Expense: %d\n\n", income, expense);
        add_transaction(&income, &expense, &current_balance, history, &history_count);
        printf("\n\n\nYOUR BALANCE: Rs. %d\n\n\n", current_balance);
        printf("Income: %d \t | Expense: %d\n\n", income, expense);
        display_history(history, history_count);
        save_history(history, history_count);

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
    xd = getchar();
    if (xd != 'y' && xd != 'Y') {
        printf("We hope to see you again!");
        exit(0); // Exit the program if user chooses not to continue
    }
}

/*-----------------------------------------Add Transaction------------------------------------------*/
void add_transaction(int *income, int *expense, int *current_balance, History history[], int *history_count) {
    char ch;
    int amount = 0;

    printf("\n\nDo you want to add expense or income? (Enter 'e' for expense & 'i' for income)\n");
    scanf(" %c", &ch);

    if (ch == 'e' || ch == 'E') {
        printf("Enter expense: ");
        scanf("%d", &amount);
        *expense += amount;
        *current_balance -= amount;

        char category[20];
        printf("Enter category:\n");
        printf("1. Food\n");
        printf("2. Entertainment\n");
        printf("3. Education\n");
        printf("4. Others\n");
        int category_choice;
        scanf("%d", &category_choice);

        switch (category_choice) {
            case 1:
                strcpy(category, "Food");
                break;
            case 2:
                strcpy(category, "Entertainment");
                break;
            case 3:
                strcpy(category, "Education");
                break;
            case 4:
                strcpy(category, "Others");
                break;
            default:
                printf("Invalid category\n");
                break;
        }

        history[*history_count].amount = amount;
        history[*history_count].transaction_type = 'e';
        strcpy(history[*history_count].transaction_detail, category);
        (*history_count)++;
    } else if (ch == 'i' || ch == 'I') {
        printf("Enter income: ");
        scanf("%d", &amount);
        *income += amount;
        *current_balance += amount;

        history[*history_count].amount = amount;
        history[*history_count].transaction_type = 'i';
        strcpy(history[*history_count].transaction_detail, "Job");
        (*history_count)++;
    } else {
        printf("Invalid input. Please enter 'e' for expense or 'i' for income.");
    }
}

/*----------------------------------Function to display transaction history------------------------------------------*/
void display_history(History history[], int history_count) {
    printf("\n\n----- Transaction History -----\n");
    for (int i = history_count - 1; i >= 0; i--) {
        printf("%d. ", history_count - i);
        if (history[i].transaction_type == 'e') {
            printf("Spent Rs. %d on %s\n", history[i].amount, history[i].transaction_detail);
        } else if (history[i].transaction_type == 'i') {
            printf("Earned Rs. %d income\n", history[i].amount);
        }
    }
}

/*------------------------ Function to save transaction history to a file------------------------------------*/
void save_history(History history[], int history_count) {
    FILE *fp = fopen("transaction_history.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < history_count; i++) {
        fprintf(fp, "Transaction %d:\n", i + 1);
        if (history[i].transaction_type == 'e') {
            fprintf(fp, "Spent Rs. %d on %s\n", history[i].amount, history[i].transaction_detail);
        } else if (history[i].transaction_type == 'i') {
            fprintf(fp, "Earned Rs. %d income\n", history[i].amount);
        }
    }

    fclose(fp);
}
