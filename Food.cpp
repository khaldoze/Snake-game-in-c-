#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;
extern int cellSize;
extern int cellCount;
extern Color darkGreen;
extern Color green;
extern int offset;

bool ElementInDeque(Vector2 element, deque<Vector2> dequee);

//!-------------------
class Food
{
    public:
     Vector2 position ;
     Texture2D  texture; 
     Food( deque<Vector2> snakeBody)
     {
        Image image = LoadImage("food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
     }
     ~Food()
     {
        UnloadTexture(texture);
     }

     void Draw()
     {
       DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
     }
     
      Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

     
     Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateRandomCell();
        while (ElementInDeque(position, snakeBody))
        {
            position = GenerateRandomCell();
        }
        return position;
    }
};

bool ElementInDeque(Vector2 element, deque<Vector2> dequee)
{
    for (unsigned int i = 0; i < dequee.size(); i++)
    {
        if (Vector2Equals(dequee[i], element))
        {
            return true;
        }
    }
    return false;
}


