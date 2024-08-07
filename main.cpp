#include <iostream>
#include <raylib.h>
#include "game.h"

using namespace std;

double lastUpdateTime = 0;

bool EventTriggered(double interval){
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main () {

    InitWindow(500, 620, "tetris test"); 

    SetTargetFPS(60);

    //Font font = LoadFontEx("Font/Bread Coffee.ttf", 64, 0, 0);

    Grid grid = Grid ();
    TBlock blockT = TBlock ();
    
    Game game = Game();
    grid.Print();

    while (!WindowShouldClose()) 
	{
        UpdateMusicStream(game.music);
        game.HandleInput();
       
        if (EventTriggered(0.2)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Score", 350, 40, 38, WHITE);
        DrawText(TextFormat(" %d", game.score), 373, 90, 40, RED);
        DrawText("Next Block:", 330, 200, 28, WHITE);
        game.DrawTextGameOver();  //!בלי עזרה 
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
}
