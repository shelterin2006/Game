#pragma once
#include "gamedefs.h"

class Card {
private:
    Image a;
    Texture2D image;
    Rectangle button;
    bool useRectangle;
    Vector2 point, current_point;
    Vector2 large = {100, 100};
    float scaleSmall = 0.02f, scaleLarge = 0.05;
    float rotation = 0.0f;
public:
    Card(){};
    void inputNoRec(Texture2D a, float b, Vector2 c);
    void drawCardScale(const float &a) const;
    void freeTexture2D() const;
    bool checkMove() const;
    Vector2 getPoint() const {return point;}
    void resetPoint(){current_point = point;}
    void setLargePoint(){current_point = large;}
    void move(Vector2 target);
};