#include "card.h"

void Card::drawCardScale(const float& a, const Vector2& point) const  {
    DrawTextureEx(image, point , rotation, a, WHITE);
}
void Card::deleteTexture2D() const {
    UnloadTexture(image);
}
bool Card::CheckRec() {
    return CheckCollisionPointRec(GetMousePosition(), button);
}
bool Card::IsPressed() {
    return CheckRec() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
void Card::inputNoRec(Texture2D a, float b) {
    image = a; useRectangle = false; rotation = b;
}

