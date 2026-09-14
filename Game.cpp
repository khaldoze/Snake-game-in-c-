#include <iostream>
#include <raylib.h>
#include <deque>    
#include <raymath.h>
#include "Food.cpp"
#include "Snake.cpp"
using namespace std;
extern int cellSize;
extern int cellCount;
extern Color darkGreen;
extern Color green;

class Game
{
    public:
         Snake snake = Snake();
         Food food = Food(snake.body);
         bool running = true;
         int score = 0;

         Sound eatSound;
         Sound wallSound;

        Game()
        {
            InitAudioDevice();
            eatSound = LoadSound("Sounds_eat.mp3");
            wallSound = LoadSound("Sounds_wall.mp3");
        }

            ~Game()
            {
                UnloadSound(eatSound);
                UnloadSound(wallSound);
                CloseAudioDevice();
            }

            void Draw()
            {
                food.Draw();
                snake.Draw();
            }

            void Update()
            {
                if (running)
                {
                    snake.Update();
                    CollesionWithFood();
                    CheckCollisionWithEdges(); 
                    CheckCollisionWithTail();
                }
            }

            void CollesionWithFood()
            {
                if(Vector2Equals(snake.body[0],food.position))
                {
                    food.position = food.GenerateRandomPos(snake.body);
                    snake.AddSegmant = true;
                    score++;
                    PlaySound(eatSound);
                }
            }

        void CheckCollisionWithEdges()
        {
            if (snake.body[0].x == cellCount || snake.body[0].x == -1)
            {
                GameOver();
            }
            if (snake.body[0].y == cellCount || snake.body[0].y == -1)
            {
                GameOver();
            }
        }

            void GameOver()
            {   
                 snake.Reset();
                 food.position = food.GenerateRandomPos(snake.body);
                 running = false;
                 score = 0;
                 PlaySound(wallSound);
            }

             void CheckCollisionWithTail()
            {
                deque<Vector2> headlessBody = snake.body;
                headlessBody.pop_front();
                if (ElementInDeque(snake.body[0], headlessBody))
                {
                    GameOver();
                }
            }

};


