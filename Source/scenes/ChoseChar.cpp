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
    const char *playText = "Back";
    int fontSize = 20;
    int textWidth = MeasureText(playText, fontSize);
    int textX = back.x + (back.width - textWidth) / 2;
    int textY = back.y + (back.height - fontSize) / 2; // căn giữa theo chiều dọc
    DrawText(playText, textX, textY, fontSize, BLACK);

    DrawRectangleRec(charSirin, BLUE);
    const char *SirinText = "Sirin";
    fontSize = 20;
    textWidth = MeasureText(playText, fontSize);
    textX = charSirin.x + (charSirin.width - textWidth) / 2;
    textY = charSirin.y + (charSirin.height - fontSize) / 2; // căn giữa theo chiều dọc
    DrawText(SirinText, textX, textY, fontSize, BLACK);

    DrawRectangleRec(charTeriri, GREEN);
    const char *TeririText = "Teriri";
    fontSize = 20;
    textWidth = MeasureText(playText, fontSize);
    textX = charTeriri.x + (charTeriri.width - textWidth) / 2;
    textY = charTeriri.y + (charTeriri.height - fontSize) / 2; // căn giữa theo chiều dọc
    DrawText(TeririText, textX, textY, fontSize, BLACK);
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
