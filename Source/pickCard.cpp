#include "pickCard.h"

pick::pick(Card u[], int c, Card s[], int d) {
    n = c, m = d;
    for (int i = 0; i < n; i++) use[i] = u[i];
    for (int i = 0; i < m; i++) select[i] = s[i];
    isDragging = false;
    offset = { 0.0f, 0.0f };
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
        if (Utils::isPressed(use[i])) {
            updateCard(&use[i]);
        } else if (Utils::isPressed(select[i])) {
            updateCard(&select[i]);
        }
    }
}

#include "raylib.h"


void pick::updateCard(Card *box)
{
    Vector2 mousePoint = GetMousePosition();
    Rectangle b = box->getButton();
    bool collision = CheckCollisionPointRec(mousePoint, b);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && collision)
    {
        isDragging = true;
        offset.x = mousePoint.x - b.x;
        offset.y = mousePoint.y - b.y;
    }
    if (isDragging)
    {
        b.x = mousePoint.x - offset.x;
        b.y = mousePoint.y - offset.y;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isDragging = false;
        }
    }
    box->updateButton(b);
}

void pick::display() {
    DrawRectangleRec(back, RED);
    DrawRectangleRec(playGame, ORANGE);

}


