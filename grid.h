#pragma once
#include <vector>
#include <raylib.h>

class Grid 
{
public:
    Grid();
    void Initialize();
    void Draw();
    int grid [20] [10];
    void Print();
    bool isCellOutside(int row, int col);
    bool IsCellEmpty(int row, int col);
    int ClearFullRows();

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);

    int numRows;
    int numColumns;
    int cellSize;
    std::vector<Color> colors;


    
};