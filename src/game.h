#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <vector>

class Game
{
private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    void Reset();
    bool BlockFits();

public:
    Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool isGameOver;
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    Grid grid;
};