#pragma once
#include "raylib.h"

class Card {
private:

public:
    Texture2D image;
    Rectangle button;
    bool useRectangle;
    float rotation, scaleSmall, scaleLarge;
    void inputNoRec(Texture2D a, float b);
    void drawCardScale(const float &a, const Vector2 &point) const;
    void deleteTexture2D() const;
    bool CheckRec();
    bool IsPressed();
};