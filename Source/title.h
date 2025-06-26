#pragma once
#include "utils.h"
class Title {
private:
    Rectangle howToPlay{}, play{}, credits{};
    Texture2D bg{};
public:
    Title() {
        const float t = Utils::centered(100, screenWidth);
        howToPlay = {t, 50, 100, 50};
        play = {t, 150, 100, 50};
        credits = {t, 250, 100, 50};
        bg = LoadTexture("resources/bg.png");
    }
    ~Title(){UnloadTexture(bg);}
    void display() const;
    int behavior();
};