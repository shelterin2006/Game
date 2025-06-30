#pragma once
#include "card.h"
#include "utils.h"
class pick {
private:
    int n, m;
    Card use[10], select[10];
    Rectangle playGame{}, back{};
    Vector2 offset;
    bool isDragging;

public:
    pick()= default;
    pick(Card a[], int n, Card b[], int m);
    void behavior();
    void display();
    void updateCard(Card *box);
};