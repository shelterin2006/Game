#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include "raylib.h"
#include "raymath.h"
#include <random>
#include <functional>
#include <stdexcept>
#include <any>
#include <utility>
using namespace std;

inline mt19937 rng(static_cast<int>(std::chrono::steady_clock::now().time_since_epoch().count()));
inline int rnd(const int x, const int y) {
    return uniform_int_distribution<int>(x, y)(rng);
}

class Utils {
public:
    static float centered(float sizeIndex, float sizeWindow) {
        return (sizeWindow / 2.0f) - (sizeIndex / 2.0f);
    }
    static float right(float sizeIndex, float sizeWindow) {
        return sizeWindow - 20.0f - sizeIndex;
    }
    static bool checkRec(const Rectangle& a) {
        return CheckCollisionPointRec(GetMousePosition(), a);
    }
    static bool isPressed(const Rectangle& a) {
        return checkRec(a) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }
};