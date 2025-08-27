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
    const char *playText = "Play";
    int fontSize = 20;
    int textWidth = MeasureText(playText, fontSize);
    int textX = play.x + (play.width - textWidth) / 2;
    int textY = play.y + (play.height - fontSize) / 2; // căn giữa theo chiều dọc
    DrawText(playText, textX, textY, fontSize, BLACK);

    // Ví dụ cho Credits
    DrawRectangleRec(credits, GREEN);
    const char *creditsText = "Credits";
    textWidth = MeasureText(creditsText, fontSize);
    textX = credits.x + (credits.width - textWidth) / 2;
    textY = credits.y + (credits.height - fontSize) / 2;
    DrawText(creditsText, textX, textY, fontSize, BLACK);
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
