#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define ENTER 13
#define TAB 9
#define BACKSPACE 8
#define MAX_TRANSACTIONS 100

typedef struct History 
{
    int amount;
    char transaction_type;//expense or income
    char transaction_detail[20];
    int current_balance; //detail of the transaction (e.g. category like food, entertainment etc.)
    int interest;
} History;


void login();
void username();
void add_transaction(int *saving_income, int *original_income,int *income, int *expense, int *current_balance, int *food, int *entertainment, int *education, int *others, History history[], int *history_count,int savings);
void display_history(History history[], int history_count);
void save_history(History history[], int history_count, int current_balance,int expense,int incomex,int savings,int saving_income,int original_income);
void history_fp(int *current_balance,int *expense,int *incomex,int savings,int *saving_income,int *original_income);
int main() {
	int expense=0, current_balance=0;
    int food = 0, entertainment = 0, education = 0, others =0;
    History history[MAX_TRANSACTIONS];
    int history_count=0;
    int incomex=0,savings=0;
    int saving_income=0,original_income=0;
    login();
    history_fp(&current_balance,&expense,&incomex,savings,&saving_income,&original_income);
    int income=incomex;
    
    while (1) {
        //system("cls");
        printf("\n\n\nYOUR BALANCE: Rs. %d\n\n\n", current_balance);
        printf("Total Income: %d \t Original Income before savings: %d \t\tsavings Income: %d \t| Expense: %d \t\n\n", income,original_income,saving_income, expense);
        add_transaction(&saving_income,&original_income,&income, &expense, &current_balance, &food, &entertainment, &education, &others, history, &history_count,savings);
        printf("\n\n\nYOUR BALANCE: Rs. %d\n\n\n", current_balance);
        printf("Total Income: %d \t Original Income before savings: %d \t \tsavings Income: %d \t| Expense: %d \t\n\n", income,original_income,saving_income,expense);
        display_history(history, history_count);
        save_history(history, history_count,current_balance,expense,incomex,savings,saving_income,original_income);

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
void add_transaction(int *saving_income,int *original_income,int *income, int *expense, int *current_balance, int *food, int *entertainment, int *education, int *others, History history[], int *history_count, int savings) {
    char ch;
    int amount=0;

    printf("\n\nDo you want to add expense or income? (Enter 'e' for expense & 'i' for income & 's' for savings)\n");
    scanf(" %c", &ch);

    if (ch == 'e' || ch == 'E') {
        printf("Enter expense: ");
        scanf("%d", &amount);
        *expense += amount;
        *current_balance -= amount;

        char category[100];
        printf("Enter category:\n");
        printf("1. Food\n");
        printf("2. Entertainment\n");
        printf("3. Education\n");
        printf("4. Others\n");
        int category_choice;
        scanf("%d", &category_choice);
        getchar();
        switch (category_choice) {
            case 1:
                *food += amount;
                strcpy(category, "Food");
                break;
            case 2:
                *entertainment += amount;
                strcpy(category, "Entertainment");
                break;
            case 3:
                *education += amount;
                strcpy(category, "Education");
                break;
            case 4:
                *others += amount;
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
    }

    else if (ch == 'i' || ch == 'I') {
        printf("Enter income: ");
        scanf("%d", &amount);
        if(*saving_income==0)
        {
        *income +=amount+*saving_income;
        }
        else
        {
        	*income +=amount;
		}
        *original_income=*income-*saving_income;
        *current_balance += amount;
        history[*history_count].amount = amount;
        history[*history_count].transaction_type = 'i';
        (*history_count)++;
    }
    else if (ch == 's' || ch == 'S') {
    	int time=0;
    	int original_income2=0;
    	int original_income1;
    	float savings1,savings5,savings10;
    	char category[100];
        printf("Enter savings:\n ");
        scanf("%d", &amount);
        savings += amount;
        if(amount<=*current_balance)
        {
        original_income2=savings;
        original_income1=savings;
        savings1=(original_income2)+(0.03)*(original_income2);
        savings5=(original_income2)+(0.05)*(original_income2);
        savings10=(original_income2)+(0.1)*(original_income2);
        printf("For time:1 year you will get %.2f\n",savings1);
        printf("For time:5 years you will get %.2f\n",savings5);
        printf("For time:10 years you will get %.2f\n",savings10);
        printf("how long do you want to save?\n");
        scanf("%d",&time);
        switch(time)
        {
        	 case 1:
                savings=savings1;
                strcpy(category, "one year");
                break;
            case 5:
                savings = savings5;
                strcpy(category, "five years");
                break;
            case 10:
                savings= savings10;
                strcpy(category, "ten years");
                break;
            default:
            	printf("invalid time period.Please enter 1 , 5 or 10");
            	break;
		}
        *current_balance -= amount;
        *saving_income=*saving_income+savings-original_income1;
        *current_balance=*current_balance+savings;
        *income =*current_balance+*expense;
        *original_income=*income-*saving_income;
        history[*history_count].amount = amount;
        history[*history_count].interest = savings;
        history[*history_count].transaction_type = 's';
        strcpy(history[*history_count].transaction_detail, category);
        (*history_count)++;
    }
}
    
    else {
        printf("Invalid input. Please enter 'e' for expense or 'i' for income.");
    }

}

/*----------------------------------Function to display transaction history------------------------------------------*/
void display_history(History history[], int history_count) {
    printf("\n\n----- Transaction History -----\n");
      for (int i = history_count - 1; i >= 0; i--) {
        printf("Transaction %d:\n", history_count - i);
        if (history[i].transaction_type == 'e') { 
            printf("Spent Rs. %d on %s\n", history[i].amount, history[i].transaction_detail);
        } else if (history[i].transaction_type == 'i') {
            printf("Earned Rs. %d income\n", history[i].amount);
        }
        else 
        {
        	printf("Saved Rs. %d for %s which becomes %d\n", history[i].amount, history[i].transaction_detail, history[i].interest);
		}
    }
}


/*------------------------ Function to save transaction history to a file------------------------------------*/
void save_history(History history[], int history_count, int current_balance,int expense,int incomex,int savings,int saving_income,int original_income) {
	FILE *fp=fopen("transaction_3.txt","w");
   if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    incomex=current_balance+expense;
    original_income=incomex-saving_income;
    fprintf(fp, "current balance:%d\n", current_balance);
    fprintf(fp,"Total income:%d\n",incomex);
    fprintf(fp,"Original income before savings:%d\n",original_income);
    fprintf(fp,"savings income:%d\n",saving_income);
    fprintf(fp,"expense:%d\n", expense);
     for (int i = history_count - 1; i >= 0; i--) {
        fprintf(fp, "Transaction %d:\n", history_count - i);
        if (history[i].transaction_type == 'e') { 
            fprintf(fp, "Spent Rs. %d on %s\n", history[i].amount, history[i].transaction_detail);
        } else if (history[i].transaction_type == 'i') {
            fprintf(fp, "Earned Rs. %d income\n", history[i].amount);
        }
        else {
            fprintf(fp, "Saved Rs. %d for %s which becomes %d\n", history[i].amount, history[i].transaction_detail, history[i].interest);
    }
}
    fclose(fp);
   
}

//Function to display saved history
void history_fp(int *current_balance,int *expense,int *incomex,int savings,int *saving_income,int *original_income){
    FILE *fp;
    fp = fopen("transaction_3.txt", "r");
    if (fp == NULL)
    {
        printf("\nNo saved data available\n");
    }
    else {
        char filechar;
        printf("\n\nYour saved data are as follows\n");
        if (fscanf(fp, "current balance:%d\n", current_balance) == 1) {
            printf("\nYour current balance: Rs. %d\n", (*current_balance));
        } else {
            printf("Error reading current balance from the file.\n");
        }
        if (fscanf(fp, "Total income:%d\n", incomex) == 1) {
            printf("Your income: Rs. %d\n", *incomex);
        } else {
            printf("Error reading income from the file.\n");
        }
        if (fscanf(fp, "Original income before savings:%d\n",original_income) == 1) {
            printf("Your Original income before savings: Rs. %d\n", *original_income);
        } else {
            printf("Error reading income from the file.\n");
        }
        if (fscanf(fp, "savings income:%d\n",saving_income) == 1) {
            printf("Your savings income: Rs. %d\n", *saving_income);
        } else {
            printf("Error reading income from the file.\n");
        }
          if (fscanf(fp, "expense:%d\n", expense) == 1) {
            printf("Your expense: Rs. %d\n", *expense);
        } 
        	else {
            printf("Error reading expense from the file.\n");
        }
	
        while((filechar=fgetc(fp)) != EOF){
            putchar(filechar);
        }
    }
    fclose(fp);
}

