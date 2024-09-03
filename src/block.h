#pragma once
#include <vector>
#include <map> // is like an dictionary in C#
#include "position.h"
#include "color.h"

class Block
{
private:
    int cellSize;
    int rotationState;
    int blockOffset;
    std::vector<Color> color;
    int row_offset;
    int col_offset;
public:
    Block();
    void Draw();
    void Move(int row, int coll);
    int id;
    std::vector<Position> GetCellPosition();
    std::map<int, std::vector<Position>> cells;
    void Rotate();
    void UndoRotation();
};