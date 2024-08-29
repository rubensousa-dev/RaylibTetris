#include <raylib.h>

int main()
{
    const float width {300};
    const float height {600};

    InitWindow(width, height, "Tetris raylib");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(WHITE);

    }
    EndDrawing();
    CloseWindow();
    return 0;    
}