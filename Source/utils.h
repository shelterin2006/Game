#pragma once
#include "gamedefs.h"
#include "card.h"
extern GameScreen currentScreen;
extern int screenWidth;
extern int screenHeight;
extern string title;
extern int FrameRate;

class Utils {
public:
    static float centered(float sizeIndex, float sizeWindow);
    static float right(float sizeIndex, float sizeWindow);

    static bool checkRec(const Rectangle& a);
    static bool isPressed(const Rectangle& a);
    static bool isPressed(const Card& a);
};