#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
private:
    int numRows;
    int numCols;
    int cellSize;
    int gridOffset;
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    std::vector<Color> colors;
    bool IsRowFull(int row);
public:
    Grid();
    ~Grid();
    int grid[20][10];
    int ClearFullRows();
    void Initialize();
    void Print();
    void Draw();

    bool IsCellOutside(int row, int collumn);
    bool IsCellEmpty(int row, int collumn);
};