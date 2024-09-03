#include "grid.h"
#include <iostream>
#include "color.h"

// this is the conscrutor == "A constructor is a special member function that is called automatically when an object is created."
Grid::Grid() 
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    gridOffset = 11;
    Initialize();
    colors = GetCellColors();
}

Grid::~Grid() {}

int Grid::ClearFullRows()
{
    int completed = 0;

    for (int row = numRows -1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed ++;
        }else if(completed >0){
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            grid [row][col] = 0;
        }   
    }
}

void Grid::Print(){
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            std::cout<< grid [row][col] << " ";
        }
        std::cout<< std::endl;
    }
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
          int cellValue = grid[row][col];
          DrawRectangle(col * cellSize + gridOffset, row * cellSize + gridOffset, cellSize -1, cellSize -1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int collumn)
{
    if (row >= 0 && row < numRows && collumn >= 0 && collumn < numCols)
    {
        return false;
    }
    return true;
        
}

bool Grid::IsCellEmpty(int row, int collumn)
{

    if (grid[row][collumn] == 0)
    {
        return true;
    }
    return false;
}

bool Grid::IsRowFull(int row)
{
    for (int collumn = 0; collumn < numCols; collumn++)
    {
        if (grid[row][collumn]== 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int collumn = 0; collumn < numCols; collumn++)
    {
        grid[row][collumn] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for (int collumn = 0; collumn < numCols; collumn++)
    {
        grid[row + numRows][collumn] = grid[row][collumn];
        grid[row][collumn] = 0;
    }
}
