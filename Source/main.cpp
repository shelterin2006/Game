#include <string>
#include "character.h"
#include "raylib.h"
#include  "raymath.h"
#include "turn.h"
#include <iostream>
using namespace std;
int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
    float scale = 0.05f;
    TurnState i = PLAYER_TURN;
    Texture2D c = LoadTexture("resources/1.jpeg");
    character a = {10, {0, 200}};
    character b = {7, {650, 200}};
    int f = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureEx(c, a.point, 0.0f, scale ,WHITE);
            DrawTextureEx(c, b.point, 0.0f, scale ,WHITE);
            if (i == PLAYER_TURN) {
                DrawText("tr", 55, 55, 20, BLACK);
            }
            else if (i == ENEMY_TURN) {
                DrawText(std::to_string(a.hp).c_str(), 455, 55, 20, BLACK);
            }
            f++;
            if (f % 30 == 0) {
                NextTurn(&i);
                if (i == PLAYER_TURN) {
                    b.hp--;
                }
                else if (i == ENEMY_TURN) {
                    a.hp--;
                }
            }
        DrawRectangle(10, 10, 100, 10, LIGHTGRAY);
        DrawRectangle(10, 10, (a.hp*100/10), 10, RED);
        DrawRectangle(600, 10, 100, 10, LIGHTGRAY);
        DrawRectangle(600, 10, (b.hp*100/8), 10, RED);
        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(c);
    return 0;
}
