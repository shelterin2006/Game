#include "pickCard.h"

pick::pick(Card a[], int n, Card b[], int m) {
    this->n = n, this->m = m;
    for (int i = 0; i < n; i++) use[i] = a[i];
    for (int i = 0; i < m; i++) select[i] = b[i];
    playGame = {1100, 650, 100, 60};
    back = {0, 0, 100, 60};
}

void pick::behavior() {
    if (Utils::isPressed(playGame)) {
        currentScreen = GAMEPLAY;
        return;
    }
    if (Utils::isPressed(back)) {
        currentScreen = TITLE;
        return;
    }
    for (int i = 0; i < n; i++) {
        use[i].updateCard();
    }
    for (int i = 0; i < m; i++) {
        select[i].updateCard();
    }
}

void pick::display() {
    DrawRectangleRec(back, RED);
    DrawRectangleRec(playGame, ORANGE);
    for (int i = 0; i < n; i++) use[i].drawCard();
    for (int i = 0; i < m; i++) select[i].drawCard();
}


