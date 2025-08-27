#pragma once
#include "../utils/gamedefs.h"
#include "../core/scene.h"
#include "mainMenu.h"
enum class BattleState {
    START_BATTLE,
    PROCESS_NEXT_ACTION,
    ENEMY_TURN,
    BATTLE_OVER, ANIMATING_ACTION, BREAKTIME,
};
class IAction;
struct QueuedAction {
    std::unique_ptr<IAction> action;
    string caster; // Ai thực hiện hành động enemy
    string target; // Ai là mục tiêu  player
    int idCard;
    QueuedAction(std::unique_ptr<IAction> act, string src, string tgt, int a);
    // Copy constructor (deep copy)
    QueuedAction(const QueuedAction& other);
    // Copy assignment
    QueuedAction& operator=(const QueuedAction& other);
};

class BattleScene : public Scene {
private:
    BattleState currentState;
    std::vector<QueuedAction> actionQueue; // Nếu cần, thay void bằng IAction hoặc class mới
    std::vector<QueuedAction> actionQueue_2; // Nếu cần, thay void bằng IAction hoặc class mới
    Rectangle back{};
    Texture2D bg;
public:
    int cardPlay;
    float timeerrr = 0.0f;
    vector<int> id1, id2;
    BattleScene();
    void onEnter(Game& game) override;
    void update(Game& game) override;
    void draw(Game& game) override;
    void onExit(Game& game) override;
    void BuildBattleQueue(Game &game);
    void SetupCard(Game &game);
    void SetupAnimation(Game &game);
};