#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block {
public:
    Block();
    void Draw(int offsetX, int offsetY);
    std::vector<Position> GetCellPosition();
    int id;
    std::map<int, std::vector<Position>> cells;
    int rowOffset;
    int colOffset;
    void Move(int, int);

    void Rotate();
    void UndoRotation();
    

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
};