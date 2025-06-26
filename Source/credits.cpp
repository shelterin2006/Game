#include "credits.h"

void Credits::display() const {
    DrawTexture(bg, 0, 0, WHITE);
    DrawRectangleRec(back, GRAY);
    DrawText("Back", 0, 0, 20, BLACK);
    DrawText("Viet cc gi do vao", 200, 200, 40, BLACK);
}

int Credits::behavior() {
    if (Utils::isPressed(back)) {
        currentScreen = TITLE;
    }
}
