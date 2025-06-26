#include "card.h"

void Card::drawCardScale(const float& a) const  {
    DrawTextureEx(image, current_point , rotation, a, WHITE);
}
void Card::freeTexture2D() const {
    UnloadTexture(image);
}
void Card::inputNoRec(Texture2D a, float b, Vector2 c) {
    image = a; useRectangle = false; rotation = b;
    point = current_point = c;
}
bool Card::checkMove() const {
    Vector2 a = point; a.x -= 50;
    return a == current_point;
}

void Card::move(Vector2 target) {
    float distance = Vector2Distance(target, current_point);
    Vector2 direc = Vector2Subtract(target, current_point);
    float pixelperframe = 200.0f * GetFrameTime();
    Vector2 mov = Vector2Scale(Vector2Normalize(direc), pixelperframe);
    if (Vector2Length(mov) >= distance) {
        current_point = target;
    } else current_point = Vector2Add(current_point, mov);
}