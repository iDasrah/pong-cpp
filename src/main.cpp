#include <iostream>
#include <raylib.h>

using namespace std;

int main () {
    const int width = 1280;
    const int height = 720;

    cout << "Starting the game..." << endl;

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(width, height, "Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawLine(width / 2, 0, width / 2, height, WHITE); // drawing center line
        DrawCircle(width / 2, height / 2, 10, WHITE); // drawing ball
        DrawRectangle(10, height / 2 - 50, 10, 100, WHITE); // drawing left paddle
        DrawRectangle(width - 20, height / 2 - 50, 10, 100, WHITE); // drawing right paddle

        EndDrawing();
    }
    

    CloseWindow();
}