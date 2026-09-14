#include <iostream>
#include <raylib.h>
#include <deque>    
#include <raymath.h>
#include "Game.cpp"
using namespace std;

Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};
int cellSize = 30;
int cellCount = 25;
int offset = 75;
double LastUpdateTime =0;

bool eventTriggered(double interval)
{
    double CurrentTime = GetTime();
     if (CurrentTime - LastUpdateTime >= interval)
     {
        LastUpdateTime = CurrentTime;
        return true;
     }
     return false; 
}

int main ()
{
    cout << "Starting the game..." << endl;
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Khaldoze Snake");
    InitAudioDevice();

    Music bgMusic;
    bool hasBgMusic = false;
    if (FileExists("bg.mp3"))
    {
        bgMusic = LoadMusicStream("bg.mp3");
        bgMusic.looping = true;
        SetMusicVolume(bgMusic, 0.999f);
        PlayMusicStream(bgMusic);
        hasBgMusic = true;
    }

    Game game = Game();
    while (WindowShouldClose() == false)
    {
        if (hasBgMusic)
        {
            UpdateMusicStream(bgMusic);
        }

        BeginDrawing();

        if (eventTriggered(0.150))
        {
            game.Update();
        }
        //! moooooooooooooooooooooooving
            if ( IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
            {
                    game.snake.direction = {0,-1};
                    game.running = true;
            }
             if ( IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
            {
                    game.snake.direction = {0,1};
                    game.running = true;
            }
             if ( IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
            {
                    game.snake.direction = {-1,0};
                    game.running = true;
            }
             if ( IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
            {
                    game.snake.direction = {1,0};
                    game.running = true;
            }

        //!
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);
        DrawText("Khaldoze Snake", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("Score : %i", game.score), GetScreenWidth() - 220, 20, 28, darkGreen);
        //! drawing
        game.Draw();

        EndDrawing();
    }

    if (hasBgMusic)
    {
        UnloadMusicStream(bgMusic);
    }
    CloseAudioDevice();
    CloseWindow();
}