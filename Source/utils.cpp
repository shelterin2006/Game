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
    Vector2 b = a.getPoint();
    return checkRec({b.x, b.y, 100, 100})
    && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}