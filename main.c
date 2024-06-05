#include <stdio.h>
#include <string.h>
#include "include/raylib.h"

#define MAX_INPUT_CHARS 20

/*--------------------------------------types and structures definition-----------------------------------*/
typedef enum GameScreen { LOGIN = 0, HOME, ANALYSIS, DETAILED,  HISTORY } SCREEN;

typedef struct History {
    int data;
    char transaction_type;
    char transaction_detail[20];
}History;

void saveHistory(History history[], int history_count);

/*--------------------------------------Program main entry point------------------------------------------*/
int main(void)
{

    /*-------------------------------Initialization------------------------------------------------------*/
    const int screenWidth = 1500;
    const int screenHeight = 990;

    InitWindow(screenWidth, screenHeight, "Sikka | Personal Finance System");
    Texture2D texture  = LoadTexture ("./img/sikkalogo.png");
    SCREEN currentScreen = LOGIN;

    //font load
    Font myfont1 = LoadFontEx("resources/Poppins-Bold.ttf", 200, 0, 0);
    Font myfont2 = LoadFontEx("resources/Poppins-Regular.ttf", 200, 0, 0);

    //colors
    Color backgrounddarker = (Color){209, 224, 222, 255};
    Color backgroundligher = (Color){224, 228, 231, 255}; // Light gray
    Color header = (Color){0,139,139, 255};
    Color buttoncolor =(Color) {218, 143, 25, 255};
    Color darkred=(Color) {160, 40, 40, 255};
    Color mediumred = (Color) {220, 80, 80, 255};
    Color lightred = (Color) {255, 120, 120, 255};
    Color palered = (Color) {255, 180, 180, 255};

    // Username variables
    char username[MAX_INPUT_CHARS + 1] = "\0";
    int usernameLetterCount = 0;
    Rectangle usernameTextBox = {screenWidth/2.0f - 80, 240, 250, 50};
    bool usernameMouseOnText = false;

    // Password variables
    char password[MAX_INPUT_CHARS + 1] = "\0";
    int passwordLetterCount = 0;
    Rectangle passwordTextBox = {screenWidth/2.0f - 80, 330, 250, 50};
    bool passwordMouseOnText = false;

    //Balance variables
    int income=0, expense =0, food=0, entertainment=0, education = 0, others=0, saving=0, time=0, interest=0;
    int current_balance= income - expense;
    Rectangle amountBox = {250, 600, 250, 50};
    Rectangle timeBox = {250, 720, 250, 50};
    bool amountMouseOnText = false;
    bool timeMouseOnText = false;
    int amount=0;
    int history_count=0, amt=0;
    History history[10];

    //buttons
    Rectangle addIncomeButton = {560, 600, 180, 40};
    Rectangle addFoodButton = {760, 660, 180, 40};
    Rectangle addEducationButton = {760, 710, 180, 40};
    Rectangle addEntertainmentButton = {760, 760, 180, 40};
    Rectangle addOthersButton = {760, 810, 180, 40};
    Rectangle goToAnalysisButton = {screenWidth/2+ 180, 45, 150, 50};
    Rectangle goToDetailsButton = {1000, 200, 200, 100};
    Rectangle goToHistory = {screenWidth/2+360, 45, 150, 50}; 
    Rectangle exitButton = { screenWidth/2 + 540, 45, 150, 50 };
    Rectangle homeButton = { screenWidth/2, 45, 150, 50 };
    Rectangle addSaveButton = {250, 790, 180, 40};
    Rectangle addTimeButton = {460, 790, 180, 40};


    int framesCounter = 0;          // Useful to count frames

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)

    /*-------------------------------------------main loop ------------------------------------------*/

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (CheckCollisionPointRec(GetMousePosition(),usernameTextBox))
            usernameMouseOnText =true;
        else usernameMouseOnText = false;

        if(CheckCollisionPointRec(GetMousePosition(), passwordTextBox))
            passwordMouseOnText = true;
        else passwordMouseOnText = false;

        if (CheckCollisionPointRec(GetMousePosition(), amountBox))
            amountMouseOnText = true;
        else amountMouseOnText = false;

        if(CheckCollisionPointRec(GetMousePosition(), timeBox))
            timeMouseOnText = true;
        else timeMouseOnText = false;

        /*---------------------------------------Username textbox input----------------------------------------*/
        if (usernameMouseOnText)
        {
            //Get char pressed on the queue (unicode character)
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125] i.e printable characters
                if ((key >= 32) && (key <= 125) && (usernameLetterCount < MAX_INPUT_CHARS))
                {
                    username[usernameLetterCount] = (char)key;//(char)- explicitly convert the integer key to a character type
                    username[usernameLetterCount+1] = '\0'; // Add null terminator at the end of the string.
                    usernameLetterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                usernameLetterCount--;
                if (usernameLetterCount < 0) usernameLetterCount = 0;
                username[usernameLetterCount] = '\0';
            }
        }

        /*--------------------------------------- Password textbox input------------------------------------*/
        if (passwordMouseOnText)
        {
            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (passwordLetterCount < MAX_INPUT_CHARS))
                {
                    password[passwordLetterCount] = (char)key;
                    password[passwordLetterCount + 1] = '\0'; // Add null terminator at the end of the string.
                    passwordLetterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                passwordLetterCount--;
                if (passwordLetterCount < 0) passwordLetterCount = 0;
                password[passwordLetterCount] = '\0';
            }
        }

        if (CheckCollisionPointRec(GetMousePosition(), amountBox))
            amountMouseOnText = true;
        else
            amountMouseOnText = false;

/*---------------------------------------Amount textbox input----------------------------------------*/
if (amountMouseOnText)
{
    // Get char pressed (unicode character) on the queue
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0)
    {
        // Check if the entered character is a digit
        if ((key >= '0') && (key <= '9'))
        {
            // Convert the character to its numerical value and update the amount
            amount = amount * 10 + (key - '0');
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        // Handle backspace to delete digits from the amount
        amount /= 10;
    }
}
/*----------------------------Time Text Box--------------------------------*/
if (timeMouseOnText)
{
    // Get char pressed (unicode character) on the queue
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0)
    {
        // Check if the entered character is a digit
        if ((key >= '0') && (key <= '9'))
        {
            // Convert the character to its numerical value and update the amount
            time = time * 10 + (key - '0');
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        // Handle backspace to delete digits from the amount
        time /= 10;
    }
}

/*-------------------------------------------Button Clicks Updates------------------------------------------------------*/
       if (CheckCollisionPointRec(GetMousePosition(), addIncomeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            income += amount;
            current_balance = income - expense;
            amt=amount;
            amount = 0;

            history[history_count].data = amt;
            history[history_count].transaction_type = 'i';
            saveHistory(history, history_count);
            (history_count)++;
       }

        if(CheckCollisionPointRec(GetMousePosition(), addFoodButton)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            expense += amount;
            current_balance = income-expense;
            amt=amount;
            food +=amount;
            amount = 0;

            history[history_count].data = amt;
            history[history_count].transaction_type = 'e';
            strncpy(history[history_count].transaction_detail, "food", sizeof(history[history_count].transaction_detail));
            saveHistory(history, history_count);
            (history_count)++;
        }

        if(CheckCollisionPointRec(GetMousePosition(), addEducationButton)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            expense += amount;
            current_balance = income-expense;
            amt=amount;
            education +=amount;
            amount = 0;
            history[history_count].data = amt;
            history[history_count].transaction_type = 'e';
            strncpy(history[history_count].transaction_detail, "education", sizeof(history[history_count].transaction_detail));
            saveHistory(history, history_count);
            (history_count)++;
            
        }
        if(CheckCollisionPointRec(GetMousePosition(), addEntertainmentButton)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            expense += amount;
            current_balance = income-expense;
            entertainment +=amount;
            amt=amount;
            amount = 0;
            history[history_count].data = amt;
            history[history_count].transaction_type = 'e';
            strncpy(history[history_count].transaction_detail, "entertainment", sizeof(history[history_count].transaction_detail));
            saveHistory(history, history_count);
            (history_count)++;
        }
        if(CheckCollisionPointRec(GetMousePosition(), addOthersButton)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            expense += amount;
            current_balance = income-expense;
            amt=amount;
            others +=amount;
            amount = 0;
            history[history_count].data = amt;
            history[history_count].transaction_type = 'e';
            strncpy(history[history_count].transaction_detail, "others", sizeof(history[history_count].transaction_detail));
            saveHistory(history, history_count);
            (history_count)++;
        }
        if (CheckCollisionPointRec(GetMousePosition(), addTimeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            interest = interest + (amt * 0.09 * time)/100;
            time = 0;
        }
        if(CheckCollisionPointRec(GetMousePosition(), addSaveButton)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            saving += amount;
            amt=amount;
            amount = 0;
            history[history_count].data = amt;
            history[history_count].transaction_type = 's';
            strncpy(history[history_count].transaction_detail, "Saving", sizeof(history[history_count].transaction_detail));
           saveHistory(history, history_count);
            (history_count)++;
        }

     /*   if (usernameMouseOnText || passwordMouseOnText) framesCounter++;
        else framesCounter = 0;*/

/*--------------------------------------Switch cases for switching to different screens---------------------------------------------------------*/
        switch(currentScreen)
        {
            case LOGIN:
            {
                if (strcmp(username, "Yurisha") == 0 && strcmp(password, "password") == 0)
                {
                    currentScreen = HOME;
                }
            } break;

            case HOME:
            {
                if (CheckCollisionPointRec(GetMousePosition(), homeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    currentScreen=HOME;
                }
                if (CheckCollisionPointRec(GetMousePosition(), goToAnalysisButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = ANALYSIS;
                }
                else if (CheckCollisionPointRec(GetMousePosition(), goToHistory) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = HISTORY;
                }
                else if(CheckCollisionPointRec(GetMousePosition(), exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    CloseWindow();
                    return 0;
                }
            } break;

            case ANALYSIS:
            {
               if (CheckCollisionPointRec(GetMousePosition(), goToDetailsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = DETAILED;
                }
                if (CheckCollisionPointRec(GetMousePosition(), homeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    currentScreen=HOME;
                }
                if (CheckCollisionPointRec(GetMousePosition(), goToAnalysisButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = ANALYSIS;
                }
                else if (CheckCollisionPointRec(GetMousePosition(), goToHistory) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = HISTORY;
                }
                else if(CheckCollisionPointRec(GetMousePosition(), exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    CloseWindow();
                    return 0;
                }
            } break;

            case DETAILED:
                if (CheckCollisionPointRec(GetMousePosition(), goToAnalysisButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = ANALYSIS;
                 }
                break;
            
            case HISTORY:
            {
                if (CheckCollisionPointRec(GetMousePosition(), homeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    currentScreen=HOME;
                }
                if (CheckCollisionPointRec(GetMousePosition(), goToAnalysisButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = ANALYSIS;
                }
                else if (CheckCollisionPointRec(GetMousePosition(), goToHistory) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = HISTORY;
                }
                else if(CheckCollisionPointRec(GetMousePosition(), exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    CloseWindow();
                    return 0;
                }
            } break;
            default: break;
        }

/*-------------------------------------------------------------------------------Draw---------------------------------------------------------------*/
        BeginDrawing();{
            switch(currentScreen)
            {
                case LOGIN:
                {
                    ClearBackground(WHITE);
                    DrawRectangle(0, 0, screenWidth, screenHeight, backgrounddarker);
                    //DrawRectangle(200, 130, 800, 480, RAYWHITE);
                    Rectangle destRect = {15,15, texture.width/5, texture.height/5};
                    DrawTexturePro(texture, (Rectangle) { 0, 0, texture.width, texture.height}, destRect, (Vector2) { 0,0}, 0.0f, RAYWHITE);//Vector2{0,0} specifies the origin of rotation and scaling will be performed around the top left corner of the texture but 0.0f means rotation angle of texture and it's set to zero, meaning no rotation.
                    DrawTextEx(myfont1, "Personal Finance System", (Vector2){120, 40}, 50, 2, BLACK);
                    DrawTextEx(myfont1, "LOGIN", (Vector2){ 190, 170 }, 40, 2, DARKBROWN);

                    DrawTextEx(myfont1, "Please enter your name:", (Vector2){190, 240}, 30, 2, BROWN);
                    
                    // Draw Username Textbox
                    DrawRectangleRec(usernameTextBox, RAYWHITE);
                    if (usernameMouseOnText) DrawRectangleLines((int)usernameTextBox.x, (int)usernameTextBox.y, (int)usernameTextBox.width, (int)usernameTextBox.height, GREEN);
                    else DrawRectangleLines((int)usernameTextBox.x, (int)usernameTextBox.y, (int)usernameTextBox.width, (int)usernameTextBox.height, DARKGRAY);
                    DrawTextEx(myfont2, username, (Vector2){(int)usernameTextBox.x + 5, (int)usernameTextBox.y + 8}, 40, 2, DARKGREEN);

                    DrawTextEx(myfont1, "Enter password:", (Vector2){190, 330}, 30, 2, BROWN);
                    // Draw Password Textbox
                    DrawRectangleRec(passwordTextBox, RAYWHITE);
                    if (passwordMouseOnText) DrawRectangleLines((int)passwordTextBox.x, (int)passwordTextBox.y, (int)passwordTextBox.width, (int)passwordTextBox.height, GREEN);
                    else DrawRectangleLines((int)passwordTextBox.x, (int)passwordTextBox.y, (int)passwordTextBox.width, (int)passwordTextBox.height, DARKGRAY);
                    DrawTextEx(myfont2, password, (Vector2){(int)passwordTextBox.x + 5, (int)passwordTextBox.y + 8}, 40, 2, DARKGREEN);

                    DrawTextEx(myfont1, "Place mouse over the text box to enter!", (Vector2){190, 450}, 20, 2, GRAY);

                    DrawTextEx(myfont2, TextFormat("Username chars: %i/%i", usernameLetterCount, MAX_INPUT_CHARS), (Vector2){190, 280}, 22, 2, DARKGRAY);
                    DrawTextEx(myfont2, TextFormat("Password char: %i/%i", passwordLetterCount, MAX_INPUT_CHARS), (Vector2) {190, 370}, 22, 2, DARKGRAY);
  
            if (usernameMouseOnText || passwordMouseOnText)
            {
                if (usernameLetterCount < MAX_INPUT_CHARS || passwordLetterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)usernameTextBox.x + 8 + MeasureText(username, 40), (int)usernameTextBox.y + 12, 40, GREEN);
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)passwordTextBox.x + 8 + MeasureText(password, 40), (int)passwordTextBox.y + 12, 40, GREEN);
                }
               // else DrawText("Press BACKSPACE to delete chars...", 230, 350, 20, GRAY);
            }

                } break;
                case HOME:
                {
                    ClearBackground(WHITE);
                    DrawRectangle(0, 140, screenWidth, screenHeight, backgroundligher);
                    DrawRectangle(0, 0, screenWidth, 140, header);
                    Rectangle destRect = {15,15, texture.width/5, texture.height/5};
                    DrawTexturePro(texture, (Rectangle) { 0, 0, texture.width, texture.height}, destRect, (Vector2) { 0,0}, 0.0f, WHITE);
                    DrawTextEx(myfont1, "Personal Finance System", (Vector2){120, 40}, 50, 2, WHITE);
                    // buttons to change screen 
                    DrawRectangleRec(homeButton, buttoncolor);
                    DrawTextEx(myfont1, "Home",(Vector2) {homeButton.x + 20, homeButton.y + 15}, 25, 2, WHITE); 
                    DrawRectangleRec(goToAnalysisButton, buttoncolor);
                    DrawTextEx(myfont1, "Analysis",(Vector2) {goToAnalysisButton.x + 20, goToAnalysisButton.y + 15}, 25, 2, WHITE);
                    DrawRectangleRec(goToHistory, buttoncolor);
                    DrawTextEx(myfont1, "History",(Vector2) {goToHistory.x + 20, goToHistory.y + 15}, 25, 2, WHITE);
                    DrawRectangleRec(exitButton, buttoncolor);
                    DrawTextEx(myfont1, "Exit",(Vector2) {exitButton.x + 20, exitButton.y + 15}, 25, 2, WHITE);
                    DrawTextEx(myfont1, "PERSONAL INFORMATION:", (Vector2) {120, 180}, 40, 2, BLACK);
                    DrawTextEx(myfont2, "Username: Yurisha Bajracharya\n\n\nOccupation: Student\n\n\nDOB: 2061-07-20\n\n\nEmail:yurisha@gmail.com\n\n\nPhone:9834000000", (Vector2) {120, 230}, 25, 2,DARKGRAY);
                    DrawTextEx(myfont1,"CURRENT STATUS:", (Vector2) {820, 180}, 40, 2, BLACK);
                    char balanceText[100];
                    snprintf(balanceText, sizeof(balanceText), "Current Balance: %d", current_balance);
                    DrawTextEx(myfont1, balanceText, (Vector2) {820, 250}, 25, 2, DARKGREEN);
                    char incomeText[100];
                    snprintf(incomeText, sizeof(incomeText), "Income: %d", income);
                    DrawTextEx(myfont1, incomeText, (Vector2) {820, 290}, 25, 2, DARKGREEN);
                    char expenseText[100];
                    snprintf(expenseText, sizeof(expenseText), "Expense: %d", expense);
                    DrawTextEx(myfont1, expenseText, (Vector2){820, 320}, 25, 2, DARKGREEN);
                    char savingText[100];
                    snprintf(savingText, sizeof(savingText), "Saving: %d", saving);
                    DrawTextEx(myfont1, savingText, (Vector2){820, 350}, 25, 2, DARKGREEN);
                    char interestText[100];
                    snprintf(interestText, sizeof(interestText), "Interest: %d(Pending)", interest);
                    DrawTextEx(myfont1, interestText, (Vector2){820, 380}, 25, 2, DARKGREEN);
                    char foodText[100];
                    char educationText[100];
                    char entertainmentText[100];
                    char othersText[100];
                    snprintf(foodText, sizeof(foodText), "Food: %d", food);
                   // DrawText(foodText, 220, 550, 20, DARKGREEN);
                    snprintf(educationText, sizeof(educationText), "Education: %d", education);
                   // DrawText(educationText, 220, 570, 20, DARKGREEN);
                    snprintf(entertainmentText, sizeof(entertainmentText), "Entertainment: %d", entertainment);
                  //  DrawText(entertainmentText, 220, 590, 20, DARKGREEN);
                    snprintf(othersText, sizeof(othersText), "Others: %d", others);
                  //  DrawText(othersText, 220, 610, 20, DARKGREEN);

                  DrawRectangle(120, 500, 1300, 400, backgrounddarker);
                    // Input income and expense
                    DrawTextEx(myfont1,"Please enter your income or expense amount:", (Vector2) {250, 550}, 30, 2, BLACK);
                    DrawRectangleRec(amountBox, backgroundligher);

                    DrawRectangleRec(addIncomeButton, header);
                    DrawTextEx(myfont1, "Add Income", (Vector2) {addIncomeButton.x + 10, addIncomeButton.y + 10}, 20, 2, WHITE);
                    
                    DrawTextEx(myfont1, "Add Expense:", (Vector2) {760, 600}, 30, 2, RED);
                    //DrawRectangleRec(addExpenseButton, RED);
                    //DrawText("Add Expense", addExpenseButton.x + 10, addExpenseButton.y + 10, 20, WHITE);
                    DrawRectangleRec(addFoodButton, mediumred);
                    DrawTextEx(myfont1, "Food", (Vector2) {addFoodButton.x+10, addFoodButton.y+10}, 20, 2, WHITE);
                    DrawRectangleRec(addEducationButton, mediumred);
                    DrawTextEx(myfont1, "Education", (Vector2) {addEducationButton.x+10, addEducationButton.y+10}, 20, 2, WHITE);
                    DrawRectangleRec(addEntertainmentButton, mediumred);
                    DrawTextEx(myfont1, "Entertainment", (Vector2) {addEntertainmentButton.x+10, addEntertainmentButton.y+10}, 20, 2, WHITE);
                    DrawRectangleRec(addOthersButton, mediumred);
                    DrawTextEx(myfont1, "Others", (Vector2) {addOthersButton.x+10, addOthersButton.y+10}, 20, 2, WHITE);
                    DrawRectangleRec(addSaveButton, header);
                    DrawTextEx(myfont1, "Save", (Vector2){addSaveButton.x+10, addSaveButton.y+10}, 20, 2, WHITE);
                    DrawTextEx(myfont1, "Enter the time in years: ", (Vector2){250, 670}, 30, 2, BLACK);
                    DrawRectangleRec(timeBox, backgroundligher);
                    //DrawRectangleRec(timeBox, GREEN);
                    DrawRectangleRec(addTimeButton, header);
                    DrawTextEx(myfont1, "Add Time", (Vector2) {addTimeButton.x+15, addTimeButton.y+10}, 20, 2, WHITE);
                     // Convert amount integer to string
                    char amountText[20]; // Assuming the amount can be represented in 20 characters
                    snprintf(amountText, sizeof(amountText), "%d", amount);
                    if (amountMouseOnText) DrawRectangleLines((int)amountBox.x, (int)amountBox.y, (int)amountBox.width, (int)amountBox.height, GREEN);
                    else DrawRectangleLines((int)amountBox.x, (int)amountBox.y, (int)amountBox.width, (int)amountBox.height, DARKGRAY);
                    DrawTextEx(myfont2, amountText, (Vector2) {(int)amountBox.x + 5, (int)amountBox.y + 8}, 40, 2, BLACK);                    char timeText[20];
                    snprintf(timeText, sizeof(timeText), "%d", time);
                    if(timeMouseOnText) DrawRectangleLines((int)timeBox.x, (int)timeBox.y, (int)timeBox.width, (int)timeBox.height, GREEN);
                    else DrawRectangleLines ((int)timeBox.x, (int)timeBox.y, (int)timeBox.width, (int)timeBox.height, DARKGRAY);
                    DrawTextEx(myfont2, timeText, (Vector2) {(int)timeBox.x+5, (int)timeBox.y+8}, 40, 2, BLACK);
                    } break;

                case ANALYSIS:
                {
                    ClearBackground(WHITE);
                    DrawRectangle(0, 140, screenWidth, screenHeight, backgroundligher);
                    DrawRectangle(0, 0, screenWidth, 140, header);
                    Rectangle destRect = {15,15, texture.width/5, texture.height/5};
                    DrawTexturePro(texture, (Rectangle) { 0, 0, texture.width, texture.height}, destRect, (Vector2) { 0,0}, 0.0f, WHITE);
                    DrawTextEx(myfont1, "Personal Finance System", (Vector2){120, 40}, 50, 2, WHITE);
                    // buttons to change screen 
                    DrawRectangleRec(homeButton, buttoncolor);
                    DrawTextEx(myfont1, "Home",(Vector2) {homeButton.x + 20, homeButton.y + 15}, 25, 2, WHITE); 
                    DrawRectangleRec(goToAnalysisButton, buttoncolor);
                    DrawTextEx(myfont1, "Analysis",(Vector2) {goToAnalysisButton.x + 20, goToAnalysisButton.y + 15}, 25, 2, WHITE);
                    DrawRectangleRec(goToHistory, buttoncolor);
                    DrawTextEx(myfont1, "History",(Vector2) {goToHistory.x + 20, goToHistory.y + 15}, 25, 2, WHITE);
                    DrawRectangleRec(exitButton, buttoncolor);
                    DrawTextEx(myfont1, "Exit",(Vector2) {exitButton.x + 20, exitButton.y + 15}, 25, 2, WHITE);
                    DrawRectangleRec(goToDetailsButton, ORANGE);
                    DrawTextEx(myfont1, "Detailed\n\nExpenditure\n\nView",(Vector2) {goToDetailsButton.x + 10, goToDetailsButton.y + 10}, 25, 2, WHITE);
                    
                    DrawTextEx(myfont1, "ANALYSIS",(Vector2) {120, 190}, 40, 2, BLACK);
                    DrawTextEx(myfont2, "Analyze your expenses and income.", (Vector2) {120, 240}, 20, 2, BLACK);
                    
                    //Index
                    DrawTextEx(myfont1, "Representation:", (Vector2) {120, 300}, 25, 2, BLACK);
                    DrawRectangle(120, 340, 25, 25, GREEN);
                    DrawTextEx(myfont2, "Income", (Vector2) {150, 340}, 25, 2, DARKGRAY);
                    DrawRectangle(120, 375, 25, 25, RED);
                    DrawTextEx(myfont2, "Expense", (Vector2) {150, 375}, 25, 2, DARKGRAY);

                    //Display Written Analysis
                    DrawTextEx(myfont1, "Financial Balance", (Vector2){300, 760}, 30, 2, BLACK);
                    if(income>expense){
                        DrawTextEx(myfont1, "Surplus", (Vector2) {300, 800}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont2, "Congratulations! You've Achieved Financial Surplus.", (Vector2){300, 830}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont1, "Message", (Vector2) {300, 860}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont2, "Great work! You're consistently spending less than you earn, which is key to financial success.", (Vector2){300, 890}, 25, 2, DARKGRAY);
                    }
                    else if (expense>income){
                        DrawTextEx(myfont1, "Deficit", (Vector2) {300, 800}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont2, "Caution! You're Operating at a Financial Deficit.", (Vector2){300, 830}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont1, "Message", (Vector2) {300, 860}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont2, "It's time to reassess your spending habits and prioritize financial stability.", (Vector2){300, 890}, 25, 2, DARKGRAY);
                    }
                    else {
                        DrawTextEx(myfont1, "Equilibrium", (Vector2) {300, 800}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont2, "Financial Equilibrium Maintained.", (Vector2){300, 830}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont1, "Message", (Vector2) {300, 860}, 25, 2, DARKGRAY);
                        DrawTextEx(myfont2, "You're maintaining a balance between your income and expenses.\n\nStay vigilant to sustain this equilibrium for future financial security.", (Vector2){300, 890}, 25, 2, DARKGRAY);
                    }


                    float incomepercent, expensepercent;
                    incomepercent=((float)income/(income+expense))*100;
                    expensepercent=((float)expense/(income+expense))*100;
                    char incomepercentText[50], expensepercentText[50];
                    snprintf(incomepercentText, sizeof(incomepercentText), ": %.2f%%", incomepercent);
                    DrawTextEx(myfont2, incomepercentText, (Vector2) {240, 340}, 25, 2, BLACK);
                    snprintf(expensepercentText, sizeof(expensepercentText), ": %.2f%%", expensepercent);
                    DrawTextEx(myfont2, expensepercentText, (Vector2){240, 375}, 25, 2, BLACK);


                    //Chart
                    float chartValues[2] = {income, expense};
                    Color colors[2] = {GREEN, RED}; // Colors for each segment
                    Vector2 center = {screenWidth / 2, screenHeight / 2};
                    float radius = screenHeight / 4;
                    float startAngle = 0;

                for(int i = 0; i < 2; i++){
                    float sweepAngle = 360 * (chartValues[i] / (income + expense));
                    DrawCircleSector(center, radius, startAngle, startAngle + sweepAngle, radius, colors[i]);
                    startAngle += sweepAngle;
                }} break;
                
                
                case DETAILED:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, backgroundligher);
                    DrawRectangle(0, 0, screenWidth, 140, header);
                    Rectangle destRect = {20,20, texture.width/5, texture.height/5};
                    DrawTexturePro(texture, (Rectangle) { 0, 0, texture.width, texture.height}, destRect, (Vector2) { 0,0}, 0.0f, backgroundligher);
                    DrawTextEx(myfont1, "Personal Finance System", (Vector2) {120, 45}, 50, 2, WHITE);
                    DrawRectangleRec(goToAnalysisButton, ORANGE);
                    DrawTextEx(myfont1, "Back",(Vector2) {goToAnalysisButton.x + 20, goToAnalysisButton.y + 15}, 25, 2, WHITE);
                    
                    DrawTextEx(myfont1, "DETAILED EXPENSE ANALYSIS",(Vector2) {120, 190}, 40, 2, BLACK);
                    DrawTextEx(myfont2, "Analyze where you are spending the most.", (Vector2) {120, 240}, 20, 2, BLACK);
                    
                    //Index
                    DrawTextEx(myfont1, "Representation:", (Vector2) {120, 300}, 25, 2, BLACK);
                    DrawRectangle(120, 340, 25, 25, darkred);
                    DrawTextEx(myfont2, "Food", (Vector2) {150, 340}, 25, 2, DARKGRAY);
                    DrawRectangle(120, 375, 25, 25, palered);
                    DrawTextEx(myfont2, "Education", (Vector2) {150, 375}, 25, 2, DARKGRAY);
                    DrawRectangle(120, 410, 25, 25, lightred);
                    DrawTextEx(myfont2, "Entertainment", (Vector2) {150, 410}, 25, 2, DARKGRAY);
                    DrawRectangle(120, 445, 25, 25, mediumred);
                    DrawTextEx(myfont2, "Others", (Vector2) {150, 445}, 25, 2, DARKGRAY);

                    //percent diplay
                    float foodpercent, educationpercent, entertainmentpercent, otherspercent;
                    foodpercent=((float)food/(food+education+entertainment+others))*100;
                    educationpercent=((float)education/(food+education+entertainment+others))*100;
                    entertainmentpercent=((float)entertainment/(food+education+entertainment+others))*100;
                    otherspercent=((float)others/(food+education+entertainment+others))*100;
                    char foodpercentText[50], educationpercentText[50], entertainmentpercentText[50], otherspercentText[50];
                    snprintf(foodpercentText, sizeof(foodpercentText), ": %.2f%%", foodpercent);
                    DrawTextEx(myfont2, foodpercentText, (Vector2) {320, 340}, 25, 2, BLACK);
                    snprintf(educationpercentText, sizeof(educationpercentText), ": %.2f%%", educationpercent);
                    DrawTextEx(myfont2, educationpercentText, (Vector2){320, 375}, 25, 2, BLACK);
                    snprintf(entertainmentpercentText, sizeof(entertainmentpercentText), ": %.2f%%", entertainmentpercent);
                    DrawTextEx(myfont2, entertainmentpercentText, (Vector2) {320, 410}, 25, 2, BLACK);
                    snprintf(otherspercentText, sizeof(otherspercentText), ": %.2f%%", otherspercent);
                    DrawTextEx(myfont2, otherspercentText, (Vector2){320, 445}, 25, 2, BLACK);

                                      
                    float chartValues[4] = {food, education, entertainment, others}; // Values for each segment of the pie chart
                    Color colors[4] = {darkred, palered, lightred, mediumred}; // Colors for each segment
                    Vector2 center = {screenWidth / 2, screenHeight / 2};
                    float radius = screenHeight / 4;
                    float startAngle = 0;

        for(int i = 0; i < 4; i++){
            float sweepAngle = 360 * (chartValues[i] / (food+education+entertainment+others));
            DrawCircleSector(center, radius, startAngle, startAngle + sweepAngle, radius, colors[i]);
            startAngle += sweepAngle;
        }
                } break;
        case HISTORY:
        {
           ClearBackground(WHITE);
                    DrawRectangle(0, 140, screenWidth, screenHeight, backgroundligher);
                    DrawRectangle(0, 0, screenWidth, 140, header);
                    Rectangle destRect = {15,15, texture.width/5, texture.height/5};
                    DrawTexturePro(texture, (Rectangle) { 0, 0, texture.width, texture.height}, destRect, (Vector2) { 0,0}, 0.0f, WHITE);
                    DrawTextEx(myfont1, "Personal Finance System", (Vector2){120, 40}, 50, 2, WHITE);
                    // buttons to change screen 
                    DrawRectangleRec(homeButton, buttoncolor);
                    DrawTextEx(myfont1, "Home",(Vector2) {homeButton.x + 20, homeButton.y + 15}, 25, 2, WHITE); 
                    DrawRectangleRec(goToAnalysisButton, buttoncolor);
                    DrawTextEx(myfont1, "Analysis",(Vector2) {goToAnalysisButton.x + 20, goToAnalysisButton.y + 15}, 25, 2, WHITE);
                    DrawRectangleRec(goToHistory, buttoncolor);
                    DrawTextEx(myfont1, "History",(Vector2) {goToHistory.x + 20, goToHistory.y + 15}, 25, 2, WHITE);
                    DrawRectangleRec(exitButton, buttoncolor);
                    DrawTextEx(myfont1, "Exit",(Vector2) {exitButton.x + 20, exitButton.y + 15}, 25, 2, WHITE);
            DrawTextEx(myfont1, "TRANSACTION HISTORY", (Vector2) {120, 190}, 40, 2, BLACK);
            
            // Open the file for reading
            FILE *fp;
            fp = fopen("transactionHistory.txt", "r");
            if (fp == NULL)
            {
                DrawText("Error opening file for reading", 120, 270, 20, DARKGRAY);
            }
            
                int transactioncount=0;
                char line[1024];
                int y = 270; // Starting y-coordinate for drawing text

                 //Read each line from the file and draw it on the screen
                while(fgets(line, sizeof(line), fp)!=NULL)
                {
                    DrawTextEx(myfont2, line, (Vector2) {120, y}, 30, 2, DARKGRAY);
                    y += 30; // Move to the next line
                    transactioncount++;
                }
                y=270;
                for(int i=0; i<transactioncount/2; i++){
                    DrawTextEx(myfont1, "-----------------------------------------------------------------------", (Vector2){120, y+60}, 10, 2, DARKGRAY);
                    y+=60;
                }
                fclose(fp);
            
        } break;

                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }}

    // De-Initialization
    // Unload all loaded data (textures, fonts)
    UnloadTexture(texture);
    UnloadFont(myfont1);
    UnloadFont(myfont2);
    CloseWindow();        // Close window and OpenGL context
    return 0;
}


bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}



void saveHistory(History history[], int history_count) {
    FILE *fp = fopen("transactionHistory.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i <= history_count; i++) {
        fprintf(fp, "Transaction %d:\n", i + 1);
        if (history[i].transaction_type == 'e') {
            fprintf(fp, "Spent Rs. %d on %s\n", history[i].data, history[i].transaction_detail);
        } else if (history[i].transaction_type == 'i') {
            fprintf(fp, "Earned Rs. %d income\n", history[i].data);
        }
        else if(history[i].transaction_type=='s'){
            fprintf(fp, "Saved Rs. %d\n", history[i].data);
        }
    }
    fclose(fp); // Close the file after writing all transactions
}