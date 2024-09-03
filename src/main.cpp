#include <raylib.h>
#include "game.h"
#include "color.h"
double lastUpdateTime = 0;

bool EventTrigger(double interval)
{    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}


void UI(Font gameFont, bool gameIsOver)
{
    DrawTextEx(gameFont, "Score", {350,15}, 38, 2, WHITE);
    DrawTextEx(gameFont, "Next", {365,175}, 38, 2, WHITE);
    if (gameIsOver)
    {
        DrawTextEx(gameFont, "GameOver", {325,450}, 30, 2, WHITE);
        DrawTextEx(gameFont, "Press R to restart", {325,550}, 16, 2, WHITE);
    }
    DrawRectangleRounded({320, 55,170,60},0.3,6, lightBlue);
    DrawRectangleRounded({320, 215,170,180},0.3,6, lightBlue);
}

int main()
{
    const float width {300};
    const float height {600};
    const float widthOffset {200};
    const float heightOffset {20};
    InitWindow(width + widthOffset, height + heightOffset, "Tetris raylib"); 
    SetTargetFPS(60);
    Font gameFont = LoadFontEx("Font/monogram.tff", 64,0,0);
    
    Game game = Game();
    while (!WindowShouldClose())
    {
        if (EventTrigger(0.5))
        {
            game.MoveBlockDown();
        }
        
        game.HandleInput();
        BeginDrawing();
        ClearBackground(darkBlue);
        UI(gameFont, game.isGameOver);

        game.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;    
}