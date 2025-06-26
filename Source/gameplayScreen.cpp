#include "gameplayScreen.h"

ScreenGamePlay::ScreenGamePlay(character a, character b, Card a1[], int m, Card b1[], int n) {
    this->c[0] = a, this->c[1] = b;
    turn = PLAYER_TURN;
    charUseCard = enemyUseCard = 0;
    MAX_cardCharacter = m, MAX_cardEnemy = n;
    for (int i = 0; i < MAX_cardCharacter; i++)
        card[i] = a1[i];
    for (int i = 0; i < MAX_cardEnemy; i++)
        card[i + 10] = b1[i];
    charTurn = true;
    as = CARD_MOVING;
}

void ScreenGamePlay::deleteTexture2D() {
    c[0].freeTexture2D(), c[1].freeTexture2D();
    Utils::freeTexture2D(card, MAX_cardCharacter);
}

void ScreenGamePlay::display() {
    //hp
    c[0].drawHp({10, 70});
    c[1].drawHp({1000, 70});

    DrawRectangleRec(returnHome, BLUE);
    DrawText("Back", 0, 0, 20, BLACK);
    c[0].drawAttack(); c[1].drawIdle();
    Vector2 v = card[0].getPoint(); v.y -= 50;
    for (int i = 0; i < MAX_cardCharacter; i++) {
        Vector2 p = {50 + static_cast<float>(i) * 50.0f, 500};
        card[i].move(v);
        card[i].drawCardScale(0.02f);
    }
    for (int i = 0; i < MAX_cardEnemy; i++) {
        Vector2 p = {900 + static_cast<float>(i) * 50.0f, 500};
        card[i + 10].drawCardScale(0.02f);
    }
}

void ScreenGamePlay::behavior() {
    if (Utils::isPressed(returnHome)) {
        currentScreen = TITLE; return;
    }
    int f = (charTurn ? charUseCard : enemyUseCard);
    Vector2 v = card[f].getPoint(); v.y -= 50;
    switch (as) {
        case CARD_MOVING:
            if (card[f].checkMove()) {
                card[f].setLargePoint();
                as = CARD_LARGE;
            } else
                card[f].move(v);
            break;
        case CARD_LARGE:

            // as = MOVING_TO_TARGET;
            break;
        case MOVING_TO_TARGET:
            as = PERFORMING_ACTION; break;
        case RETURNING:
            as = TAKING_DAMAGE; break;
        default:
            as = TAKING_DAMAGE;
    }
}
