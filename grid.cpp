#include <raylib.h>
#include "grid.h"
#include <iostream>
#include <colors.h>

using namespace std;

Grid::Grid(){
    numRows = 20;
    numColumns = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize(){
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++){
            grid [row] [col] = 0;
        }
        
    }
}

void Grid::Print(){
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++){
            std::cout << grid [row] [col] << " ";
        }
        std::cout << std::endl;
    }
}



/* 
std::vector<Color> Grid::GetCellColors () {
    // Color red = {232, 18, 18, 255};
    Color blue = {13, 64, 216, 255};
    Color orange = {226, 116, 17, 255};
    Color darkPurple = {112, 31, 126, 255};
    Color white = {255, 255, 255, 255};
    Color magenta = {255, 0, 255, 255};
    Color yellow = {253, 249, 0, 255};
    Color lime = {0, 158, 47, 255};
    Color darkGrey = {80, 80, 80, 255};
    return {darkGrey, blue, orange, darkPurple, white, magenta, yellow, lime};
} */

void Grid::Draw() {
    for (int row = 0; row < numRows; row++){
        for (int col = 0; col < numColumns; col++){
            int cellValue = grid [row] [col];

            DrawRectangle(col * cellSize+11, row * cellSize+11 , cellSize-1, cellSize-1, colors[cellValue]);
        }
    }
}

bool Grid::isCellOutside(int row, int col)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numColumns){
        return false;
    } else {
        return true;
    }
}

bool Grid::IsCellEmpty(int row, int col)
{
    if (grid[row][col] == 0 ){
        return true;
    } else {
        return false;
    }
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = numRows-1; row >= 0; row--){
        if(IsRowFull(row)){
            ClearRow(row);
            completed++;
        } else if (completed>0){
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < numColumns; column++){
        if(grid[row][column] == 0){
            return false;
        }
        
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < numColumns; column++){
        grid[row][column] = 0;
    }
   
}

void Grid::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < numColumns; column++){
        grid[row+numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}


