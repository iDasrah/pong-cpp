#include <raylib.h>

#include "Ball.h"
#include "Paddle.h"
#include "CPUPaddle.h"

using namespace std;

const int width = 1280;
const int height = 720;

int playerScore = 0;
int cpuScore = 0;

Ball ball(width / 2, height / 2, 5, 6, 10);
Paddle playerPaddle(10, height / 2 - 50, 10, 100);
CPUPaddle cpuPaddle(width - 20, height / 2 - 50, 10, 100);

int main () {

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(width, height, "Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // collision check
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{playerPaddle.x, playerPaddle.y, playerPaddle.width, playerPaddle.height})) {
            ball.speedX = -ball.speedX;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpuPaddle.x, cpuPaddle.y, cpuPaddle.width, cpuPaddle.height})) {
            ball.speedX = -ball.speedX;
        }

        // update
        ball.Update(playerScore, cpuScore);
        playerPaddle.Update();
        cpuPaddle.Update(ball.y);

        // drawing
        ClearBackground(BLACK);
        DrawLine(width / 2, 0, width / 2, height, WHITE); // drawing center line

        ball.Draw();

        playerPaddle.Draw();
        cpuPaddle.Draw();

        // draw scores
        DrawText(TextFormat("Player: %d", playerScore), 10, 10, 20, WHITE);
        DrawText(TextFormat("CPU: %d", cpuScore), width - 100, 10, 20, WHITE);

        EndDrawing();
    }
    
    CloseWindow();
}