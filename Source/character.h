#pragma once
#include "gamedefs.h"

class character {
private:

public:
    int hp;
    Vector2 point;
    Texture2D image;
    void freeTexture2D();
};