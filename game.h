#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
public:
    Game ();
    ~Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw();
    Grid grid;
    void HandleInput ();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void DrawTextGameOver(); //!בלי עזרה    
    void DrawTextScore();
    bool gameOver;
    int score;
    Music music;

private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Sound rotateSound;
    Sound addScoreSound;
};