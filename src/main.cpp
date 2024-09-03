#include <raylib.h>
#include "game.h"
#include "color.h"
#include <iostream>

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


void UI(Font gameFont, bool gameIsOver, int currentScore)
{
    DrawTextEx(gameFont, "Score", {350,15}, 38, 2, WHITE);
    DrawTextEx(gameFont, "Next", {365,175}, 38, 2, WHITE);
    if (gameIsOver)
    {
        DrawTextEx(gameFont, "GameOver", {325,450}, 30, 2, WHITE);
        DrawTextEx(gameFont, "Press R to restart", {325,550}, 16, 2, WHITE);
    }
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
    
    char scoreText[10];
    sprintf (scoreText, "%d", currentScore);
    Vector2 textSize = MeasureTextEx(gameFont, scoreText, 38, 2);
    
    DrawTextEx(gameFont, scoreText, {320 + (170 - textSize.x)/2, 67.5}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215,170,180},0.3,6, lightBlue);
}

double dificulty(int gameScore)
{
    if (gameScore <= 1000)
    {   
        return 0.4;
    }else if(gameScore > 1000 && gameScore <= 2000)
    {
        return 0.3;
    }else{
        return 0.2;
    }
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
        UpdateMusicStream(game.music);
        if (EventTrigger(dificulty(game.score)))
        {
            game.MoveBlockDown();
        }
        
        game.HandleInput();
        BeginDrawing();
        ClearBackground(darkBlue);
        UI(gameFont, game.isGameOver, game.score);

        game.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;    
}