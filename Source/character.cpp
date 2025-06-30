#include "character.h"

#include "logo.h"

void character::freeTexture2D() {
    UnloadImage(image);
    UnloadTexture(idle);
    hp = 0;
}
character::character(int a, Vector2 p, Image pic, Image b) {
    hp = a, image = pic, point = p, attack = b;
    Image t = ImageCopy(image);
    ImageResizeNN(&t, t.width * 3, t.height * 3);
    idle = LoadTextureFromImage(t);
    UnloadImage(t);
    t = ImageCopy(attack);
    ImageResizeNN(&t, t.width * 3, t.height * 3);
    ata = LoadTextureFromImage(t);
    UnloadImage(t);
}
bool character::nextFrame(int d, int numFrame) {
    time += GetFrameTime();
    if (time < (1.0f / static_cast<float>(d))) return false;
    time = 0.0f;
    currentFrame = (currentFrame + 1) % numFrame;
    frameRec.x = currentFrame * framWidth;
    return true;
}
void character::drawIdle() {
    nextFrame(6, 10);
    DrawTextureRec(idle, frameRec, point, WHITE);
}
bool character::drawAttack() {
    nextFrame(6, 7);
    DrawTextureRec(ata, frameRec, point, WHITE);
    return true;
}
bool character::move(Vector2 target) {
    float distance = Vector2Distance(target, point);
    Vector2 direc = Vector2Subtract(target, point);
    float pixelperframe = 200000.0f * GetFrameTime();
    Vector2 mov = Vector2Scale(Vector2Normalize(direc), pixelperframe);
    if (Vector2Length(mov) >= distance) {
        point = target;
        return true;
    } else point = Vector2Add(point, mov);
    return false;
}
void character::drawHp(const Vector2 p) const {
    const float f = hp * 100.0f / 10.0f;
    DrawRectangleV(p, {100, 10}, LIGHTGRAY);
    DrawRectangleV(p, {f, 10}, RED);
}

void character::truHP() {
    this->hp -= 1.0f;
    if (hp < 0.0f) hp = 0.0f;
}
