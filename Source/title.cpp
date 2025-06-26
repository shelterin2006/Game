#include "title.h"

void Title::display() const {
    DrawTexture(bg, 0, 0, WHITE);
    DrawRectangleRec(howToPlay, GRAY);
    DrawRectangleRec(play, BLUE);
    DrawRectangleRec(credit, BLACK);
}

int Title::behavior() {
    bool a = Utils::isPressed(howToPlay);
    bool b = Utils::isPressed(play);
    bool c = Utils::isPressed(credit);
    if (a) {
        currentScreen = GAMEPLAY;
    }
    if (b) {
        currentScreen = GAMEPLAY;
    }
    if (c) {
        currentScreen = GAMEPLAY;
    }
}
