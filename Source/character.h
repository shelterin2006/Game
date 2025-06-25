#pragma once
#include "raylib.h"

class character {
private:

public:
    int hp;
    Vector2 point;
    Texture2D image;
    void deleteTexture2D() {
        UnloadTexture(image);
    }
};