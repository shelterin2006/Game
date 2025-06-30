#include "utils.h"

float Utils::centered(float sizeIndex, float sizeWindow) {
    return (sizeWindow / 2.0f) - (sizeIndex / 2.0f);
}
float Utils::right(float sizeIndex, float sizeWindow) {
    return sizeWindow - 20.0f - sizeIndex;
}
bool Utils::checkRec(const Rectangle& a) {
    return CheckCollisionPointRec(GetMousePosition(), a);
}
bool Utils::isPressed(const Rectangle& a) {
    return checkRec(a) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
bool Utils::isPressed(const Card &a) {
    return checkRec(a.getButton()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Utils::freeTexture2D(const Texture2D &a) {
    UnloadTexture(a);
}
void Utils::freeTexture2D(Card a[], const int n) {
    for (int i = 0; i < n; i++) a[i].freeTexture2D();
}