#include "gamescreen.h"
float centered(float sizeIndex, float sizeWindow) {
    return (sizeWindow / 2.0f) - (sizeIndex / 2.0f);
}
float right(float sizeIndex, float sizeWindow) {
    return sizeWindow - 20.0f - sizeIndex;
}
void screenTitle() {
    Rectangle button = {100, 100, 100, 100};
    DrawRectangleRec(button, BLUE);
    if (CheckCollisionPointRec(GetMousePosition(), button)) {
        DrawText("1", 100, 100, 38, RED);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            DrawText("2", 150, 150, 38, RED);
        }
    }
}