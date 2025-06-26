#pragma once
#include "utils.h"
class Credits {
private:
    Rectangle back;
    Texture2D bg;
public:
    Credits() {
        back = {0, 0, 100, 50};
        bg = LoadTexture("resources/bg.png");
    }
    void display() const;
    int behavior();
};