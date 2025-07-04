#include <raylib.h>

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