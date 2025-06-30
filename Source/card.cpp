#include "card.h"

void Card::drawCard() const  {
    DrawTextureEx(image, current_point , rotation, scale, WHITE);
}
void Card::freeTexture2D() const {
    UnloadTexture(image);
}
void Card::inputNoRec(Texture2D image, Vector2 point, Vector2 large, float scaleSmall, float scaleLarge) {
    this->image = image; this->useRectangle = false;
    this->point = this->current_point = point;
    this->large = large;
    this->mov = point; this->mov.y -= 50;
    this->scale = this->scaleSmall = scaleSmall;
    this->scaleLarge = scaleLarge;
}
bool Card::checkMove() const {
    return mov == current_point;
}
void Card::move() {
    float distance = Vector2Distance(mov, current_point);
    Vector2 direc = Vector2Subtract(mov, current_point);
    float pixelperframe = 200.0f * GetFrameTime();
    Vector2 m = Vector2Scale(Vector2Normalize(direc), pixelperframe);
    if (Vector2Length(m) >= distance) {
        current_point = mov;
    } else current_point = Vector2Add(current_point, m);
}
void Card::resetPoint() {
    current_point = point;
    scale = scaleSmall;
}
void Card::setLargePoint() {
    current_point = large;
    scale = scaleLarge;
}

