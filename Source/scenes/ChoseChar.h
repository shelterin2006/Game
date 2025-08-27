#pragma once
#include "../core/scene.h"
#include "battleScene.h"
#include "pickCard.h"
#include "credits.h"
class ChoseChar : public Scene {
private:
    Rectangle charSirin{}, charTeriri{}, back{};
    Texture2D bg{};
public:
    string data;
    void onEnter(Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
    void onExit(Game& game) override;
};