#include <iostream>
#include <deque>
#include <raylib.h>
#include <raymath.h>
using namespace std;
extern int cellSize;
extern int cellCount;
extern Color darkGreen;
extern Color green;
extern int offset;

class Snake
{
    public:
        deque<Vector2> body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
        Vector2 direction = {1,0};
        bool AddSegmant = false;

        void Draw()
        {
            for (unsigned int i = 0; i < body.size(); i++)
            {
                float x = body[i].x;
                float y = body[i].y;
                Rectangle segment = Rectangle{offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize};
                DrawRectangleRounded(segment,0.5,6,darkGreen);
            }
        }

        void Update()
        {
            body.push_front(Vector2Add(body[0],direction));
            if (AddSegmant == true)
            {
                AddSegmant = false;

            }
            else 
            {
                body.pop_back();
            }
        }
            void Reset()
            {
                body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
                direction = {1, 0};
            }

           
};


