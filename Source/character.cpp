#include "character.h"

void character::freeTexture2D() {
    UnloadTexture(image);
    hp = 0;
}