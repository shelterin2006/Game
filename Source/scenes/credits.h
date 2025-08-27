#pragma once
#include "../utils/gamedefs.h"
#include "../core/scene.h"
#include "mainMenu.h"
class Credits : public Scene {
private:
    Rectangle back = {};
    Texture2D bg = {};
public:
    Credits();
    ~Credits() override{}
    void onEnter(Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
    void onExit(Game& game) override;
};