#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum GameScreen {
    LOGO, TITLE, MAP, GAMEPLAY, ENDING
};
float centered(float sizeIndex, float sizeWindow);
float right(float sizeIndex, float sizeWindow);
void screenTitle();