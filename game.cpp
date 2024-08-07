#include "game.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sound/backgroundMusic.mp3");
    //C:\Users\user\Desktop\soundsTetris\backgroundMusic.mp3
    PlayMusicStream(music);
    rotateSound = LoadSound("Sound/rotateSound.mp3");
    addScoreSound = LoadSound("Sound/addScore.mp3");
}

Game::~Game(){
    UnloadSound(rotateSound);
    UnloadSound(addScoreSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock(){
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }
    
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(){
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id){
        case 5:
            nextBlock.Draw(255, 280);
            break;
        case 6:
            nextBlock.Draw(255, 290);
            break;
        default:
            nextBlock.Draw(270, 279);
            break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0){
        gameOver = false;
        Reset();
    }
    switch (keyPressed){
        case KEY_LEFT:
        MoveBlockLeft();
        break;

        case KEY_RIGHT:
        MoveBlockRight();
        break; 

        case KEY_DOWN:
        MoveBlockDown();
        break;

        case KEY_UP:
        RotateBlock();
        break;
    }
}


void Game::MoveBlockLeft(){
    if (!gameOver){
    currentBlock.Move(0, -1);
    if (IsBlockOutside() || BlockFits()== false){
        currentBlock.Move(0, 1);
    }
    }
}
void Game::MoveBlockRight(){
    if (!gameOver){
    currentBlock.Move(0, 1);
    if (IsBlockOutside() || BlockFits()== false){
        currentBlock.Move(0, -1);
    }
    }
}
void Game::MoveBlockDown(){
    if (!gameOver){
    currentBlock.Move(1, 0);
    if (IsBlockOutside() || BlockFits()== false){
        currentBlock.Move(-1, 0);
        LockBlock();
    }
    }
}

void Game::DrawTextGameOver()
{
    if(gameOver == true) {
        DrawText("Game Over!", 328, 460, 28, WHITE);
    }
}


bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item: tiles){
        if (grid.isCellOutside(item.row, item.col)){
            return true;
        }
    }
    return false;

}

void Game::RotateBlock()
{
    if (!gameOver){
    currentBlock.Rotate();
    if (IsBlockOutside()|| BlockFits()== false){
        currentBlock.UndoRotation();
    } else {
        PlaySound(rotateSound);
    }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item: tiles){
        grid.grid[item.row] [item.col] = currentBlock.id;

    }
    currentBlock = nextBlock;
    if (BlockFits() == false){
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0){
        PlaySound(addScoreSound);
        UpdateScore(rowsCleared, 0);
    }
    
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item: tiles){
        if (grid.IsCellEmpty(item.row, item.col) == false){
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared){
        case 1:
        score += 10;
        break;

        case 2:
        score += 30;
        break;

        case 3:
        score += 50;
        break;

        default:
        break;
    }

    score += moveDownPoints;
}

