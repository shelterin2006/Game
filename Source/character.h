#pragma once
#include "gamedefs.h"

class character {
private:
    float hp;
    Vector2 point;
    Image image, attack;
    Texture2D idle, ata;
    int framWidth = 96*3;
    int currentFrame = 0;
    float time = 0.0f;
    Rectangle frameRec{0, 0, 96*3, 96*3};
public:
    character(){}
    character(int a, Vector2 p, Image pic, Image b);
    void freeTexture2D();
    bool nextFrame(int d, int numFrame);
    void resetFrame(){frameRec.x = 0;}
    void drawIdle();
    bool drawAttack();
    bool move(Vector2 target);
    void drawHp(Vector2 p) const;
    bool isDied() const{return hp <= 0.0f;}
    void truHP();
};