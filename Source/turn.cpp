#include "turn.h"

void NextTurn(TurnState *a, int hp1, int hp2) {
    if (hp1 <= 0 || hp2 <= 0) {
        *a = GAME_OVER;
        return;
    }
    switch (*a) {
        case PLAYER_TURN:
            *a = PLAYER_ACTION; break;
        case PLAYER_ACTION:
            *a = ENEMY_TURN; break;
        case ENEMY_TURN:
            *a = ENEMY_ACTION; break;
        default:
            *a = PLAYER_TURN;
    }
}