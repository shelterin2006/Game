#pragma once
#include "../core/scene.h"
#include "battleScene.h"
#include "pickCard.h"
#include "credits.h"
#include "ChoseChar.h"
class MainMenuScene : public Scene {
private:
    Rectangle howToPlay{}, play{}, credits{};
    Texture2D bg{};
public:
    void onEnter(Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
    void onExit(Game& game) override;
};