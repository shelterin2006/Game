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
    bool a = Utils::isPressed(howToPlay);
    bool b = Utils::isPressed(play);
    bool c = Utils::isPressed(credits);
    if (a) {
        currentScreen = GAMEPLAY;
    }
    if (b) {
        currentScreen = GAMEPLAY;
    }
    if (c) {
        currentScreen = CREDITS;
    }
}
