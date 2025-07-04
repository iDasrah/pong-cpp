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

class Paddle {
    public:
        float x, y;
        float width, height;
        int speed;

        Paddle(float startX = 10, float startY = 0, float paddleWidth = 10, float paddleHeight = 100, int paddleSpeed = 5) 
            : x(startX), y(startY), width(paddleWidth), height(paddleHeight), speed(paddleSpeed) {}

        void Draw() {
            DrawRectangle(x, y, width, height, WHITE);
        }

        void Update() {
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
                y -= speed;
            }

            if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
                y += speed;
            }

            KeepPaddleInBounds();
        }

        protected:
            void KeepPaddleInBounds() {
                if (y < 0) {
                    y = 0;
                }
                if (y + height > GetScreenHeight()) {
                    y = GetScreenHeight() - height;
                }
            }
};

class CPUPaddle : public Paddle {
    public:
        CPUPaddle(float startX = 10, float startY = 0, float paddleWidth = 10, float paddleHeight = 100, int paddleSpeed = 5) 
            : Paddle(startX, startY, paddleWidth, paddleHeight, paddleSpeed) {}

        void Update(int ballY) {
            if (y + height / 2 > ballY) {
                y -= speed;
            } else if (y + height / 2 <= ballY) {
                y += speed;
            }

            KeepPaddleInBounds();
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
    Paddle playerPaddle(10, height / 2 - 50, 10, 100);
    CPUPaddle cpuPaddle(width - 20, height / 2 - 50, 10, 100);

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
        ball.Update();
        playerPaddle.Update();
        cpuPaddle.Update(ball.y);

        // drawing
        ClearBackground(BLACK);
        DrawLine(width / 2, 0, width / 2, height, WHITE); // drawing center line

        ball.Draw();

        playerPaddle.Draw();
        cpuPaddle.Draw();

        EndDrawing();
    }
    

    CloseWindow();
}