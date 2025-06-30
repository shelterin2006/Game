#pragma once
#include "gamedefs.h"

class Card {
private:
    Rectangle button;
    Image a;
    Texture2D image;
    bool useRectangle;
    Vector2 point, current_point;
    Vector2 large;
    float scaleSmall, scaleLarge ;
    Vector2 mov;
    float rotation = 0.0f;
public:
    float scale;
    Card(){};
    void inputNoRec(Texture2D image, Vector2 point, Vector2 large, float scaleSmall, float scaleLarge);
    void drawCard() const;
    void freeTexture2D() const;
    bool checkMove() const;
    void resetPoint();
    void setLargePoint();
    void move();
    Rectangle getButton() const {return button;}
    void updateButton(Rectangle b){button = b;}
};