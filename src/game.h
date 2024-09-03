#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <vector>

class Game
{
private:
    Grid grid;
    std::vector<Block> blocks;
    std::vector<Block> GetAllBlocks();
    Block currentBlock;
    Block nextBlock;
    Block GetRandomBlock();
    bool IsBlockOutside();
    bool BlockFits();
    void MoveBlockLeft();
    void MoveBlockRight();
    void RotateBlock();
    void LockBlock();
    void Reset();
    void UpdateScore(int linesClear, int moveDownPoints);
    Sound rotateSound;
    Sound clearSound;

public:
    Game();
    ~Game();
    int score;
    int scoreIncrement;
    bool isGameOver;
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    Music music;
};