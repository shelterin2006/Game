#include "gameplayScreen.h"

ScreenGamePlay::ScreenGamePlay(character a, character b, Card a1[], int m, Card b1[], int n) {
    this->c[0] = a, this->c[1] = b;
    turn = PLAYER_TURN;
    charUseCard = 0, enemyUseCard = 10;
    MAX_cardCharacter = m; MAX_cardEnemy = n + 10;
    for (int i = 0; i < MAX_cardCharacter; i++)
        card[i] = a1[i];
    for (int i = 10; i < MAX_cardEnemy; i++)
        card[i] = b1[i - 10];
    charTurn = true;
    as = CARD_MOVING;
    nv = 0, the = 0;
}

void ScreenGamePlay::display() {
    //hp
    c[0].drawHp({10, 70});
    c[1].drawHp({1000, 70});
    DrawText(to_string(as).c_str(), 500, 500, 30, RED);
    DrawText(to_string(the).c_str(), 300, 300, 32, GRAY);
    DrawRectangleRec(returnHome, BLUE);
    DrawText("Back", 0, 0, 20, BLACK);
    c[0].drawAttack(); c[1].drawIdle();
    for (int i = 0; i < MAX_cardCharacter; i++)
        card[i].drawCard();
    for (int i = 10; i < MAX_cardEnemy; i++)
        card[i].drawCard();
}

void ScreenGamePlay::behavior() {
    if (Utils::isPressed(returnHome) || c[0].isDied() || c[1].isDied()) {
        currentScreen = TITLE; return;
    }
    switch (as) {
        case CARD_MOVING:
            if (card[the].checkMove()) {
                card[the].setLargePoint();
                as = CARD_LARGE;
            } else card[the].move();
            break;
        case CARD_LARGE:
            as = MOVING_TO_TARGET;
            break;
        case MOVING_TO_TARGET:
            as = PERFORMING_ACTION; break;
        case PERFORMING_ACTION:
            as = RETURNING; break;
        case RETURNING:
            c[nv].truHP();
            as = TAKING_DAMAGE;
            break;
        default:
            card[the].resetPoint();
            nextActor();
            as = CARD_MOVING;
    }
}

void ScreenGamePlay::nextActor() {
    if (charTurn) {
        charUseCard++;
        if (charUseCard == MAX_cardCharacter)
            charUseCard = 0;
        charTurn = false, nv = 1, the = enemyUseCard;
    } else {
        enemyUseCard++;
        if (enemyUseCard == MAX_cardEnemy)
            enemyUseCard = 10;
        charTurn = true, nv = 0, the = charUseCard;
    }
}
