#pragma once
#include "utils.h"
#include "character.h"
#include "card.h"
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
    void display();
    bool checkRec(){return Utils::checkRec(returnHome);}
    bool isPressed(){return Utils::isPressed(returnHome);}
    void behavior();
};