#include <raylib.h>

#include "Ball.h"
#include "Paddle.h"
#include "CPUPaddle.h"

const int width = 1280;
const int height = 720;

int playerScore = 0;
int cpuScore = 0;

Ball ball(width / 2, height / 2, 5, 6, 10);
Paddle playerPaddle(10, height / 2 - 50, 10, 100);
CPUPaddle cpuPaddle(width - 20, height / 2 - 50, 10, 100);

bool GameShouldStop() {
    return playerScore >= 10 || cpuScore >= 10;
}

void ResetGame() {
    playerScore = 0;
    cpuScore = 0;
    ball.Reset();
    playerPaddle.y = height / 2 - playerPaddle.height / 2;
    cpuPaddle.y = height / 2 - cpuPaddle.height / 2;
}

void DrawGameOver() {
    ClearBackground(BLACK);
    DrawText("Game Over", width / 2 - MeasureText("Game Over", 20) / 2, height / 2 - 20, 20, WHITE);
    DrawText(TextFormat("Final Score - Player: %d, CPU: %d", playerScore, cpuScore), width / 2 - MeasureText("Final Score - Player: 0, CPU: 0", 20) / 2, height / 2 + 10, 20, WHITE);
    DrawText("Press R to restart or ESC to exit", width / 2 - MeasureText("Press R to restart or ESC to exit", 20) / 2, height / 2 + 40, 20, WHITE);
}

int main () {

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(width, height, "Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (GameShouldStop()) {
            DrawGameOver();
            if (IsKeyPressed(KEY_R)) {
                ResetGame();
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                CloseWindow();
                return 0;
            }
            EndDrawing();
            continue;
        }

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