#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include "raylib.h"
#include "raymath.h"
using namespace std;

typedef enum  {
    LOGO, CREDITS, TITLE, MAP, GAMEPLAY, ENDING,
    PICKCATD
}GameScreen;
typedef enum  {
    PLAYER_TURN,
    PLAYER_ACTION,
    ENEMY_TURN,
    ENEMY_ACTION,
    GAME_OVER
}TurnState;
