#pragma once
#include "gamedefs.h"

class Card {
private:
    Texture2D image{};
    Vector2 point{}, current_point{};
    Vector2 large{};
    float scaleSmall{}, scaleLarge{} ;
    Vector2 mov{};
    float rotation = 0.0f;
    bool isDragging;
    Vector2 offset;
public:
    float scale{};
    Card()= default;
    
    // Copy constructor
    Card(const Card& other);
    
    // Assignment operator
    Card& operator=(const Card& other);
    
    // Destructor
    ~Card();
    
    void input(Texture2D& image, Vector2& point, Vector2& large, float scaleSmall, float scaleLarge);
    void drawCard() const;
    bool checkMove() const;
    void resetPoint();
    void setLargePoint();
    void move();
    Vector2 getPoint() const {return current_point;}
    void updatePoint(Rectangle b);
    void updateCard();
};
