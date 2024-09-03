#include <raylib.h>
#include "game.h"


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

int main()
{
    const float width {300};
    const float height {600};
    Color bgColor {44,44,127,255};
    InitWindow(width, height, "Tetris raylib");
    SetTargetFPS(60);
    
    Game game = Game();
    while (!WindowShouldClose())
    {
        if (EventTrigger(0.2))
        {
            game.MoveBlockDown();
        }
        
        game.HandleInput();
        BeginDrawing();
        ClearBackground(bgColor);
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;    
}