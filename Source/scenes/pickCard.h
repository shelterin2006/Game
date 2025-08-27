#pragma once
#include "../core/scene.h"
#include "../cards/DeckManager.h"
class PickCardScene : public Scene {
private:
    Rectangle playGame{}, back{}, random{};
    vector<int> chose;
    vector<Vector2> point;
    int numRandom = 0;
    Texture2D bg = {};
public:
    void onEnter(Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
    void onExit(Game& game) override;
    bool deleteChose(int a);
    void randomDesk(Game &game) ;
};