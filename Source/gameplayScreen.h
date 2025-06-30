#pragma once
#include "utils.h"
#include "character.h"
#include "card.h"

typedef enum ActorState {
    INACTIVE,           // Đang nghỉ, không làm gì.
    CARD_MOVING,
    CARD_LARGE,
    MOVING_TO_TARGET,   // Đang di chuyển tới mục tiêu.
    PERFORMING_ACTION,  // Đang thực hiện hoạt ảnh (vung kiếm, niệm phép).
    RETURNING,          // Đang quay về vị trí cũ.
    TAKING_DAMAGE,      // (Tùy chọn) Đang thực hiện hoạt ảnh nhận sát thương.
    DIED                // (Tùy chọn) Đang thực hiện hoạt ảnh chết.
} ActorState;

class ScreenGamePlay {
private:
    int charUseCard, enemyUseCard;
    int MAX_cardCharacter, MAX_cardEnemy;
    int nv, the;
    TurnState turn;
    character c[2]; //0 is hero, 1 is enemy
    Card card[21]; // 0-9 : hero, 10-19 enemy
    const Rectangle returnHome{0, 0, 100, 50};
    ActorState as;
    bool charTurn;

public:
    ScreenGamePlay() {}
    ScreenGamePlay(character a, character b, Card a1[], int m, Card b1[], int n);
    void deleteTexture2D();
    void display();
    bool checkRec() const {return Utils::checkRec(returnHome);}
    void behavior();
    void nextActor();
};