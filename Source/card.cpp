#include "card.h"

void Card::drawCardScale(const float& a, const Vector2& point) const  {
    DrawTextureEx(image, point , rotation, a, WHITE);
}
void Card::freeTexture2D() const {
    UnloadTexture(image);
}
void Card::inputNoRec(Texture2D a, float b) {
    image = a; useRectangle = false; rotation = b;
}

