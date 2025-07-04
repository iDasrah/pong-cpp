#include "Paddle.h"

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