#include "gameplayScreen.h"

ScreenGamePlay::ScreenGamePlay(character a, character b, Card a1[], int m, Card b1[], int n) {
    this->c = a, this->e = b;
    turn = PLAYER_TURN;
    charUseCard = enemyUseCard = 1;
    MAX_cardCharacter = m, MAX_cardEnemy = n;
    for (int i = 0; i < MAX_cardCharacter; i++)
        cardCharacter[i] = a1[i];
    for (int i = 0; i < MAX_cardEnemy; i++)
        cardEnemy[i] = b1[i];
}
void ScreenGamePlay::deleteTexture2D() {
    c.freeTexture2D(), e.freeTexture2D();
    Utils::freeTexture2D(cardCharacter, MAX_cardCharacter);
    Utils::freeTexture2D(cardEnemy, MAX_cardEnemy);
}

void ScreenGamePlay::display() {
    DrawRectangleRec(returnHome, BLUE);
    DrawTextureEx(c.image, c.point, 0.0f, 0.05f, WHITE);
    DrawTextureEx(e.image, e.point, 0.0f, 0.05f, WHITE);
    for (int i = 0; i < MAX_cardCharacter; i++) {
        float d = 100.0f + static_cast<float>(i) * 50.0f;
        cardCharacter[i].drawCardScale(0.1f, {d, 600});
    }
    for (int i = 0; i < MAX_cardEnemy; i++) {
        float d = 100.0f + static_cast<float>(i) * 50.0f + 500.0f;
        cardEnemy[i].drawCardScale(0.1f, {d, 600});
    }
}

void ScreenGamePlay::behavior() {
    if (isPressed()) {
        currentScreen = TITLE;
    }
}


// void gameplay() {
//     float scale = 0.05f;
//     Texture2D c = LoadTexture("resources/1.jpeg");
//     Texture2D card = LoadTexture("resources/card.png");
//     character a = {10, {20, 200}};
//     character b = {7, {right(100, 1280), 200}};
//     DrawTextureEx(c, a.point, 0.0f, scale ,WHITE);
//     DrawTextureEx(c, b.point, 0.0f, scale ,WHITE);
//     DrawTextureV(card, {100, 100} ,WHITE);
//     DrawTextureV(card, {200, 200} ,WHITE);
//     if (i == PLAYER_TURN) {
//         DrawText("tr", 55, 55, 20, BLACK);
//     }
//     else if (i == ENEMY_TURN) {
//         DrawText(std::to_string(a.hp).c_str(), 455, 55, 20, BLACK);
//     }
//     if (f % 30 == 0) {
//         NextTurn(&i);
//         if (i == PLAYER_TURN) {
//             b.hp--;
//         }
//         else if (i == ENEMY_TURN) {
//             a.hp--;
//         }
//     }
//     DrawRectangle(10, 10, 100, 10, LIGHTGRAY);
//     DrawRectangle(10, 10, (a.hp*100/10), 10, RED);
//     DrawRectangle(600, 10, 100, 10, LIGHTGRAY);
//     DrawRectangle(600, 10, (b.hp*100/8), 10, RED);
//     // UnloadTexture(c);
//     // UnloadTexture(card);
// }