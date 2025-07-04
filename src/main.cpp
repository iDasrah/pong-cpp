#include <iostream>
#include <raylib.h>

using namespace std;

class Ball {
    public:
        float x, y;
        int speedX, speedY;
        int radius;

        Ball(float startX, float startY, int startSpeedX, int startSpeedY, int ballRadius) 
            : x(startX), y(startY), speedX(startSpeedX), speedY(startSpeedY), radius(ballRadius) {}

        void Draw() {
            DrawCircle(x, y, radius, WHITE);
        }

        void Update() {
            x += speedX;
            y += speedY;

            // check for collision with walls
            if (y + radius > GetScreenHeight() || y - radius <= 0) {
                speedY = -speedY;
            }

            if (x + radius > GetScreenWidth() || x - radius <= 0) {
                speedX = -speedX;
            }
        }
};

int main () {
    const int width = 1280;
    const int height = 720;

    cout << "Starting the game..." << endl;

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(width, height, "Pong");
    SetTargetFPS(60);

    Ball ball(width / 2, height / 2, 5, 5, 10);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // update
        ball.Update();

        // drawing
        ClearBackground(BLACK);
        DrawLine(width / 2, 0, width / 2, height, WHITE); // drawing center line
        ball.Draw(); // drawing the ball
        DrawRectangle(10, height / 2 - 50, 10, 100, WHITE); // drawing left paddle
        DrawRectangle(width - 20, height / 2 - 50, 10, 100, WHITE); // drawing right paddle

        EndDrawing();
    }
    

    CloseWindow();
}