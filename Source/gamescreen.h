#pragma once
#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "turn.h"
#include "card.h"
#include <string>
typedef enum GameScreen {
    LOGO, TITLE, MAP, GAMEPLAY, ENDING
};
class ScreenGamePlay {
private:
    int charUseCard, enemyUseCard;
    int MAX_cardCharacter, MAX_cardEnemy;
    TurnState turn;
    character c{}, e{};
    Card cardCharacter[8]{}, cardEnemy[8]{};
    const Rectangle returnHome{0, 0, 100, 50};
public:
    ScreenGamePlay() {}
    ScreenGamePlay(character a, character b, Card a1[], int m, Card b1[], int n);
    void deleteTexture2D();

    static float centered(float sizeIndex, float sizeWindow);
    static float right(float sizeIndex, float sizeWindow);
    void display();
    bool checkRec() const;
    bool isPressed() const;
};
float centered(float sizeIndex, float sizeWindow);
float right(float sizeIndex, float sizeWindow);
void screenTitle();
void screenGamePlay(TurnState i, int f);