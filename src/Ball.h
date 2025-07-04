#include "raylib.h"

class Ball {
    public:
        float x, y;
        int speedX, speedY;
        int radius;

        Ball(float startX, float startY, int startSpeedX, int startSpeedY, int ballRadius) 
            : x(startX), y(startY), speedX(startSpeedX), speedY(startSpeedY), radius(ballRadius) {
                RandomizeDirection();
            }

        void Draw() {
            DrawCircle(x, y, radius, WHITE);
        }

        void Update(int &playerScore, int &cpuScore) {
            x += speedX;
            y += speedY;

            // check for collision with walls
            if (y + radius > GetScreenHeight() || y - radius <= 0) {
                speedY = -speedY;
            }

            if (x + radius > GetScreenWidth()) {
                playerScore++;
                Reset();
            } 
            
            if(x - radius <= 0) {
                cpuScore++;
                Reset();
            }
        }

    private:
        void Reset() {
            x = GetScreenWidth() / 2;
            y = GetScreenHeight() / 2;

            RandomizeDirection();
        }

        void RandomizeDirection() {
            int speedChoices[2] = {1, -1};
            speedX *= speedChoices[GetRandomValue(0, 1)];
            speedY *= speedChoices[GetRandomValue(0, 1)];
        }
};