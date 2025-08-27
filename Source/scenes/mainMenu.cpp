#include "mainMenu.h"
#include "ChoseChar.h"
#include "../core/Resource.h"
void MainMenuScene::onEnter(Game &game) {
    const float t = Utils::centered(100, Resource::getInstance().screenWidth);
    play = {t, 150, 100, 50};
    credits = {t, 250, 100, 50};
    int d = rnd(1, 5);
    bg = Resource::getInstance().getTexture2D("bg" + to_string(d));
}

void MainMenuScene::draw(Game &game) {
    DrawTexture(bg, 0, 0, WHITE);
    DrawRectangleRec(play, BLUE);
    DrawText("Play", Utils::centered(100, Resource::getInstance().screenWidth), 150, 20, BLACK);
    DrawRectangleRec(credits, GREEN);
    DrawText("Credits", Utils::centered(100, Resource::getInstance().screenWidth), 250, 20, BLACK);
}

void MainMenuScene::update(Game &game) {
    if (Utils::isPressed(play)) {
        game.switchScene(std::make_unique<ChoseChar>());
    }
    if (Utils::isPressed(credits)) {
        game.switchScene(std::make_unique<Credits>());
    }
}

void MainMenuScene::onExit(Game &game) {
    // UnloadTexture(bg);
}
