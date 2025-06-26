#pragma once
#include "utils.h"
class Title {
private:
    Rectangle howToPlay, play, credit;
    Texture2D bg;
public:
    Title() {
        const float t = Utils::centered(100, screenWidth);
        howToPlay = {t, 50, 100, 50};
        play = {t, 150, 100, 50};
        credit = {t, 250, 100, 50};
        bg = LoadTexture("resources/bg.png");
    }
    void display() const;
    bool checkRec(Rectangle a) const;
    bool isPressed(Rectangle a) const;
    int behavior();
};