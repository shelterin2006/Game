#include "readData.h"
#include "character.h"
#include  "raymath.h"
#include "turn.h"
#include "gamescreen.h"
int screenWidth = 1280;
int screenHeight = 720;
string title = "Default Title";
int FrameRate = 60;

int main()
{
    readData();
    InitWindow(screenWidth, screenHeight, title.c_str());
    SetTargetFPS(FrameRate);
    float scale = 0.05f;
    TurnState i = PLAYER_TURN;
    Texture2D c = LoadTexture("resources/1.jpeg");
    Texture2D card = LoadTexture("resources/card.png");
    character a = {10, {20, 200}};
    character b = {7, {right(100, 1280), 200}};
    int f = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            screenTitle();
            // DrawTextureEx(c, a.point, 0.0f, scale ,WHITE);
            // DrawTextureEx(c, b.point, 0.0f, scale ,WHITE);
            // DrawTextureV(card, {100, 100} ,WHITE);
            // DrawTextureV(card, {200, 200} ,WHITE);
            // if (i == PLAYER_TURN) {
            //     DrawText("tr", 55, 55, 20, BLACK);
            // }
            // else if (i == ENEMY_TURN) {
            //     DrawText(std::to_string(a.hp).c_str(), 455, 55, 20, BLACK);
            // }
            // f++;
            // if (f % 30 == 0) {
            //     NextTurn(&i);
            //     if (i == PLAYER_TURN) {
            //         b.hp--;
            //     }
            //     else if (i == ENEMY_TURN) {
            //         a.hp--;
            //     }
            // }
            // DrawRectangle(10, 10, 100, 10, LIGHTGRAY);
            // DrawRectangle(10, 10, (a.hp*100/10), 10, RED);
            // DrawRectangle(600, 10, 100, 10, LIGHTGRAY);
            // DrawRectangle(600, 10, (b.hp*100/8), 10, RED);
        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(c);
    return 0;
}
