#include "turn.h"

void NextTurn(TurnState *a) {
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