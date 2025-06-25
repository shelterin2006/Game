#pragma once
#include "raylib.h"
typedef enum TurnState {
    PLAYER_TURN,
    PLAYER_ACTION,
    ENEMY_TURN,
    ENEMY_ACTION,
    GAME_OVER
} TurnState;
void NextTurn(TurnState *a, int hp1, int hp2);