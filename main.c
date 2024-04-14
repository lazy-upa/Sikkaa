#include "raylib.h"
#include <string.h>
#include <stdio.h>


#define MAX_INPUT_CHARS 20

/*--------------------------------------types and structures definition-----------------------------------*/
typedef enum GameScreen { LOGIN = 0, HOME, ANALYSIS, HISTORY } SCREEN;

/*--------------------------------------Program main entry point------------------------------------------*/
int main(void)
{
    /*-------------------------------Initialization------------------------------------------------------*/
    const int screenWidth = 1500;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Sikka | Personal Finance System");
    Texture2D texture  = LoadTexture ("./img/logo.png");
    SCREEN currentScreen = LOGIN;

    
    // Username variables
    char username[MAX_INPUT_CHARS + 1] = "\0";
    int usernameLetterCount = 0;
    Rectangle usernameTextBox = {screenWidth/2.0f - 80, 220, 250, 50};
    bool usernameMouseOnText = false;

    // Password variables
    char password[MAX_INPUT_CHARS + 1] = "\0";
    int passwordLetterCount = 0;
    Rectangle passwordTextBox = {screenWidth/2.0f - 80, 350, 250, 50};
    bool passwordMouseOnText = false;
    
    //Balance variables
    int current_balance=0;
    int income=100, expense =0;
    Rectangle amountBox = {320, 600, 250, 50};
    
    // Function to check if a point is inside the rectangle
       /* bool CheckCollisionPointRec(Vector2 point, Rectangle rec) {
        return (point.x >= rec.x && point.x <= (rec.x + rec.width) &&
            point.y >= rec.y && point.y <= (rec.y + rec.height));
     }*/
    
    // Button structure
    /* typedef struct {
    Rectangle bounds;   // Button boundaries
    Color color;        // Button color
    const char *text;   // Button text
    } Button;

    Button button1 = {
        .bounds = { 220, 600 , 200, 100 },
        .color = GREEN,
        .text = "Go to next page"
    }; */
    
    //for invalid input
   // bool displayInvalidMessage = false;
    
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
        
        /*---------------------------------------Username textbox input----------------------------------------*/
        if (usernameMouseOnText)
        {
            //Get char pressed on the queue (unicode character)
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
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
        
         //Vector2 mousePosition = GetMousePosition();
        
        // Check if mouse is over the button
       /* if (CheckCollisionPointRec(mousePosition, button1.bounds)) 
            currentScreen=ANALYSIS;*/
        if (usernameMouseOnText || passwordMouseOnText) framesCounter++;
        else framesCounter = 0;

        switch(currentScreen)
        {
            case LOGIN:
            {
                if (strcmp(username, "yurisha") == 0 && strcmp(password, "pw") == 0)
                {
                    currentScreen = HOME;
                }
                else
                {
                  // displayInvalidMessage = true;
                }
            } break;
            case HOME:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ANALYSIS;
                }
            } break;
            case ANALYSIS:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = HISTORY;
                }
            } break;
            case HISTORY:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = HOME;
                }
            } break;
            default: break;
        }
        
/*-------------------------------------------------------------------------------Draw---------------------------------------------------------------*/
        BeginDrawing();{
            ClearBackground(RAYWHITE);
            // Draw texture
            

            switch(currentScreen)
            {
                case LOGIN:
                {
                    // TODO: Draw LOGO screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
                    Rectangle destRect = {20,20, texture.width/6, texture.height/6};
                    DrawTexturePro(texture, (Rectangle) { 0, 0, texture.width, texture.height}, destRect, (Vector2) { 0,0}, 0.0f, WHITE);
                    DrawText("Personal Finance System", 120, 40, 50, GOLD);
                    DrawText("LOGIN", 350, 150, 40, BLACK);
                    DrawText("Please enter your name:", 250, 220, 30, BROWN);
                    DrawText(username, 350, 500, 30, BLUE);
                    // Draw Username Textbox
                    DrawRectangleRec(usernameTextBox, LIGHTGRAY);
                    if (usernameMouseOnText) DrawRectangleLines((int)usernameTextBox.x, (int)usernameTextBox.y, (int)usernameTextBox.width, (int)usernameTextBox.height, RED);
                    else DrawRectangleLines((int)usernameTextBox.x, (int)usernameTextBox.y, (int)usernameTextBox.width, (int)usernameTextBox.height, DARKGRAY);
                    DrawText(username, (int)usernameTextBox.x + 5, (int)usernameTextBox.y + 8, 40, MAROON);
            
                    DrawText("Enter password:", 250, 330, 30, BROWN);
                    // Draw Password Textbox
                    DrawRectangleRec(passwordTextBox, LIGHTGRAY);
                    if (passwordMouseOnText) DrawRectangleLines((int)passwordTextBox.x, (int)passwordTextBox.y, (int)passwordTextBox.width, (int)passwordTextBox.height, RED);
                    else DrawRectangleLines((int)passwordTextBox.x, (int)passwordTextBox.y, (int)passwordTextBox.width, (int)passwordTextBox.height, DARKGRAY);
                    DrawText(password, (int)passwordTextBox.x + 5, (int)passwordTextBox.y + 8, 40, MAROON);
                    
            DrawText("Place mouse over the text box to enter!", 400, 450, 20, GRAY);

            DrawText(TextFormat("Username chars: %i/%i", usernameLetterCount, MAX_INPUT_CHARS), 300, 260, 20, DARKGRAY);
            DrawText(TextFormat("Password char: %i/%i", passwordLetterCount, MAX_INPUT_CHARS), 300, 370, 20, DARKGRAY);
          /*  if (displayInvalidMessage)
    {
        DrawText("Invalid username or password. Please recheck!", 400, 500, 30, BLACK);
    } */
            if (usernameMouseOnText || passwordMouseOnText)
            {
                if (usernameLetterCount < MAX_INPUT_CHARS || passwordLetterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)usernameTextBox.x + 8 + MeasureText(username, 40), (int)usernameTextBox.y + 12, 40, MAROON);
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)passwordTextBox.x + 8 + MeasureText(password, 40), (int)passwordTextBox.y + 12, 40, MAROON);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 350, 20, GRAY);
            }
                    
                } break;
                case HOME:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
                    DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
                    Rectangle destRect = {20,20, texture.width/6, texture.height/6};
                    DrawTexturePro(texture, (Rectangle) { 0, 0, texture.width, texture.height}, destRect, (Vector2) { 0,0}, 0.0f, WHITE);
                    DrawText("Personal Finance System", 120, 40, 50, GOLD);
                    DrawText("Personal Information:", 120, 100, 30, BLACK);
                    DrawText("Username: Yurisha Bajracharya\n\n\nOccupation: Student\n\n\nDOB: 2061-07-20\n\n\nEmail:yurisha@gmail.com\n\n\nPhone:9834000000", 120, 150, 20, DARKGRAY);
                    DrawText("CURRENT STATUS:", 120, 400, 40, BLACK);
                    char balanceText[20]; // Assuming the balance can be represented in 20 characters
                    snprintf(balanceText, sizeof(balanceText), "Current Balance: %d", current_balance);
                    DrawText(balanceText, 220, 490, 20, DARKGREEN);
                    char incomeText[20];
                    snprintf(incomeText, sizeof(incomeText), "Income: %d", income);
                    DrawText(incomeText, 220, 510, 20, DARKGREEN);
                    char expenseText[20];
                    snprintf(expenseText, sizeof(expenseText), "Expense: %d", expense);
                    DrawText(expenseText, 220, 530, 20, DARKGREEN);
                    DrawText("Do you want to enter income or expense?(- for expense)", 220, 560, 30, DARKGREEN);
                    DrawRectangleRec(amountBox, LIGHTGRAY);  
                    // Draw the button
                   /* DrawRectangleRec(button1.bounds, button1.color);
                    DrawText(button1.text, button1.bounds.x + 20, button1.bounds.y + 30, 20, WHITE);*/
                    
                    } break;
                case ANALYSIS:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, GRAY);
                    DrawText("ANALYSIS", 20, 20, 40, MAROON);
                    DrawText("Analyze your expenses and income.", 130, 220, 20, MAROON);
                    float chartValues[3] = {30.0f, 45.0f, 25.0f}; // Values for each segment of the pie chart
    Color colors[3] = {RED, BLUE, GREEN}; // Colors for each segment
        Vector2 center = {screenWidth / 2, screenHeight / 2};
        float radius = screenHeight / 4;
        float startAngle = 0;

        for(int i = 0; i < 3; i++){
            float sweepAngle = 360 * (chartValues[i] / 100);
            DrawCircleSector(center, radius, startAngle, startAngle + sweepAngle, radius, colors[i]);
            startAngle += sweepAngle;
        }


                } break;
                case HISTORY:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }}

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // Unload all loaded data (textures, fonts, audio) here!
    UnloadTexture(texture);
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


