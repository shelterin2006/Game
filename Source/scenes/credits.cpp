#include "credits.h"

Credits::Credits() {
    back = {0, 0, 100, 50};
}

void Credits::onEnter(Game &game) {
    back = {0, 0, 100, 50};
    int d = rnd(1, 5);
    bg = Resource::getInstance().getTexture2D("bg" + to_string(d));
}

void Credits::draw(Game &game) {
    DrawTexture(bg, 0, 0, WHITE);
    DrawRectangleRec(back, GRAY);
    DrawText("Back", 0, 0, 20, BLACK);
    DrawText("Open source: ", 200, 200, 40, BLACK);
    DrawText("https://github.com/shelterin2006/Game", 200, 250, 40, BLACK);
}
void Credits::update(Game &game) {
    if (Utils::isPressed(back)) {
        game.switchScene(std::make_unique<MainMenuScene>());
    }
}
void Credits::onExit(Game &game) {
    // UnloadTexture(bg);
}
