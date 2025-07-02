#include "title.h"

void Title::display() const {
    DrawTexture(bg, 0, 0, WHITE);
    DrawRectangleRec(howToPlay, GRAY);
    DrawText("HowToPlay", Utils::centered(100, screenWidth), 50, 20, BLACK);
    DrawRectangleRec(play, BLUE);
    DrawText("Play", Utils::centered(100, screenWidth), 150, 20, BLACK);
    DrawRectangleRec(credits, GREEN);
    DrawText("Credits", Utils::centered(100, screenWidth), 250, 20, BLACK);
}

int Title::behavior() {
    if (Utils::isPressed(howToPlay)) {
        currentScreen = GAMEPLAY;
    }
    if (Utils::isPressed(play)) {
        currentScreen = PICKCATD;
    }
    if (Utils::isPressed(credits)) {
        currentScreen = CREDITS;
    }
}
