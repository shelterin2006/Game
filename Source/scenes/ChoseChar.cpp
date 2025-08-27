#include "ChoseChar.h"

void ChoseChar::onEnter(Game &game) {
    const float t = Utils::centered(100, Resource::getInstance().screenWidth);
    back = {t, 50, 100, 50};
    charSirin = {t, 100, 100, 50};
    charTeriri = {t, 150, 100, 50};
    int d = rnd(1, 5);
    bg = Resource::getInstance().getTexture2D("bg" + to_string(d));
}

void ChoseChar::draw(Game &game) {
    DrawTexture(bg, 0, 0, WHITE);
    DrawRectangleRec(back, GRAY);
    DrawText("back", Utils::centered(100, Resource::getInstance().screenWidth), 50, 20, BLACK);
    DrawRectangleRec(charSirin, BLUE);
    DrawText("Sirin", Utils::centered(100, Resource::getInstance().screenWidth), 100, 20, BLACK);
    DrawRectangleRec(charTeriri, GREEN);
    DrawText("Teriri", Utils::centered(100, Resource::getInstance().screenWidth), 150, 20, BLACK);
}

void ChoseChar::update(Game &game) {
    if (Utils::isPressed(back)) {
        game.switchScene(std::make_unique<MainMenuScene>());
    }
    if (Utils::isPressed(charSirin)) {
        data = "Sirin";
        game.switchScene(std::make_unique<PickCardScene>());
    }
    if (Utils::isPressed(charTeriri)) {
        data = "TeRiRi";
        game.switchScene(std::make_unique<PickCardScene>());
    }
}

void ChoseChar::onExit(Game &game) {
    // UnloadTexture(bg);
    game.requestSceneChange(std::make_unique<BattleScene>(), data);
}
