#include "card.h"

// Copy constructor
Card::Card(const Card& other) {
    image = other.image;
    point = other.point;
    current_point = other.current_point;
    large = other.large;
    mov = other.mov;
    rotation = other.rotation;
    scale = other.scale;
    scaleSmall = other.scaleSmall;
    scaleLarge = other.scaleLarge;
}

// Assignment operator
Card& Card::operator=(const Card& other) {
    image = other.image;
    point = other.point;
    current_point = other.current_point;
    large = other.large;
    scale = other.scale;
    scaleSmall = other.scaleSmall;
    scaleLarge = other.scaleLarge;
    mov = other.mov;
    rotation = other.rotation;
    return *this;
}

// Destructor
Card::~Card() {
}

void Card::drawCard() const  {
    DrawTextureEx(image, current_point, rotation, scale, WHITE);
}
void Card::input(Texture2D& image, Vector2& point, Vector2& large, float scaleSmall, float scaleLarge) {
    this->image = image;
    this->point = this->current_point = point;
    this->large = large;
    this->mov = point; this->mov.y -= 50;
    this->scale = this->scaleSmall = scaleSmall;
    this->scaleLarge = scaleLarge;
    isDragging = false; offset = {0.0f, 0.0f};
}
bool Card::checkMove() const {
    return mov == current_point;
}
void Card::move() {
    float distance = Vector2Distance(mov, current_point);
    Vector2 direc = Vector2Subtract(mov, current_point);
    float pixelperframe = 200.0f * GetFrameTime();
    Vector2 m = Vector2Scale(Vector2Normalize(direc), pixelperframe);
    if (Vector2Length(m) >= distance) {
        current_point = mov;
    } else current_point = Vector2Add(current_point, m);
}
void Card::resetPoint() {
    current_point = point;
    scale = scaleSmall;
}
void Card::setLargePoint() {
    current_point = large;
    scale = scaleLarge;
}
// void Card::updatePoint(Rectangle b) {
//     current_point =
// }
void Card::updateCard() {
    Vector2 mousePoint = GetMousePosition();
    Rectangle bounds = {current_point.x, current_point.y, 100, 150};
    if (CheckCollisionPointRec(mousePoint, bounds) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (!isDragging) {
            offset.x = mousePoint.x - current_point.x;
            offset.y = mousePoint.y - current_point.y;
            std::cout << "Bắt đầu kéo! " << isDragging << std::endl;
        }
        isDragging = true;
    }
    if (isDragging) {
        current_point.x = mousePoint.x - offset.x;
        current_point.y = mousePoint.y - offset.y;
        if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
            isDragging = false;
            std::cout << "Dừng kéo!" << std::endl;
        }
    }
}