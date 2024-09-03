#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    color = GetCellColors();
    row_offset = 0;
    col_offset = 0;
}

void Block::Draw()
{
    std::vector<Position> tiles = GetCellPosition();
    for (Position item : tiles)
    {
        DrawRectangle(item.collumn* cellSize + 1, item.row * cellSize + 1, cellSize - 1, cellSize - 1, color[id] );
    }
}
void Block::Move(int row, int coll)
{
    row_offset +=row;
    col_offset += coll; 

}

std::vector<Position> Block :: GetCellPosition()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;

    for (Position item : tiles)
    {
        Position newPos = Position(item.row + row_offset, item.collumn + col_offset);
        movedTiles.push_back(newPos); // add to the list 
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState ++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
    
}

void Block::UndoRotation()
{
    rotationState --;
    if (rotationState == -1)
    {
        rotationState = cells.size()- 1;
    }
}
