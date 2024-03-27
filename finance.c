#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define ENTER 13
#define TAB 9
#define BACKSPACE 8

void login();
void username();

int main(){
    int choice;
    login();
    do{
        system("cls");
        printf("\n\n\t\t\t-----CATEGORIES-----\n");
        printf("\t\t\t1. Food and Drinks\n");
        printf("\t\t\t2. Shopping\n");
        printf("\t\t\t3. Housing\n");
        printf("\t\t\t4. Transportation\n");
        printf("\t\t\t5. Vehicle\n");
        printf("\t\t\t6. Life and Entertainment\n");
        printf("\t\t\t7. Financial Expenses\n");
        printf("\t\t\t8. Investments\n");
        printf("\t\t\t9. Exit\n");
        printf("\n\n Enter your choice: ");
        scanf("%d", &choice);
        system("cls");

        switch(choice){
            case 1:
            printf("You've entered the category: Food and Drinks");
            break;
            case 2:
            printf("You've entered the category: Shopping)");
            break;
            case 3:
            printf("You've entered the category: Housing)");
            break;
            case 4:
            printf("You've entered the category: Transportation)");
            break;
            case 5:
            printf("You've entered the category: Vehicle)");
            break;
            case 6:
            printf("You've entered the category: Life and Entertainment)");
            break;
            case 7:
            printf("You've entered the category: Financial Expenses)");
            break;
            case 8:
            printf("You've entered the category: Investments)");
            break;
            case 9:
            printf("Thank you for using our system :))");
            break;
            default:
            printf("Enter a valid choice");
            break;
        }
    } while(choice!=9);
    return 0;
}

void login(){
    char xd;
    printf("\n\t\t\t\t-----Welcome to Login Page-----");
    printf("\nPress 'y' to continue else Press any other key to exit");
    xd = getch();
    if (xd == 'y' || xd == 'Y')
    {
    username();
    }
    else
    {
        printf("We hope to see you again!");
    }
}


void username(){
    char user[]={"upahar"};
	char pass[]={"password"};
	char a[20];
	char ch,pwd[20];
	int c,d,i=0;
	printf("\n\t\t\t     USERNAME: ");
	scanf("%s",&a);
	printf("\n\t\t\t     PASSWORD: ");
	while((ch=getch())!=ENTER){
		pwd[i]=ch;
		if(ch== '\b'){
			printf("\b \b");
			if(i>0){
                i--;
            }
            continue;
		}
		else{
			printf("*");
			i++;
		}
	}
	pwd[i]='\0';
	c=strcmp(a,user);
	d=strcmp(pwd,pass);
	if(c!= 0|| d!=0){
		printf("\n\t\t\tinvalid username or password\n");	
        login();
	}
}