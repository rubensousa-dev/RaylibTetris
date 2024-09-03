#include "game.h"
#include <random>

Game::Game()
{
    score = 0;
    scoreIncrement = 100;
    grid = Grid();
    isGameOver = false;
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    PlayMusicStream(music);
}

Game::~Game(){
    UnloadMusicStream(music);
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;    
}


std::vector<Block> Game :: GetAllBlocks()
{
    return {IBlock(),JBlock(),LBlock(),OBlock(),SBlock(),TBlock(),ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11,11);
    switch (nextBlock.id)
    {
    case 3:
         nextBlock.Draw(255,290);
        break;
    case 4: // O block
         nextBlock.Draw(255,280);
        break;
    default:
        nextBlock.Draw(270,270);
        break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    if (isGameOver && keyPressed == KEY_R)
    {
        isGameOver = false;
        Reset();
    }

    switch (keyPressed)
    {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0,1);
            break;
        case KEY_UP:
            RotateBlock();
        default:
            break;
    }   
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.collumn))
        {
            return true;
        }
    }
    return false;
}

void Game::MoveBlockLeft()
{
    if (!isGameOver)
    {
        currentBlock.Move(0,-1);
        if (IsBlockOutside()|| BlockFits() == false)
        {
            currentBlock.Move(0,1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!isGameOver)
    {
        currentBlock.Move(0,1);
        if (IsBlockOutside()|| BlockFits() == false)
        {
            currentBlock.Move(0,-1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!isGameOver)
    {
        currentBlock.Move(1,0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1,0);
            LockBlock();
        }
    }
}
void Game :: RotateBlock()
{
    currentBlock.Rotate();
    if (IsBlockOutside())
    {
        currentBlock.UndoRotation();
    }else{
        PlaySound(rotateSound);
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();

    for(Position item : tiles)
    {
        grid.grid[item.row][item.collumn] = currentBlock.id;
    }
    currentBlock = nextBlock;

    if (!BlockFits())
    {
        isGameOver = true;
    }

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    //grid.ClearFullRows();
    if (rowsCleared >0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);    
    }
    
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesClear, int moveDownPoints)
{
    switch (linesClear)
    {
    case 1:
        score += scoreIncrement;
        break;
    case 2:
        score += (3*scoreIncrement);
        break;
    case 3:
        score += (5*scoreIncrement);
        break;
    default:
        break;
    }

    score += moveDownPoints;
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();

    for(Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.collumn) == false)
        {
            return false;
        }
    }
    return true;
}