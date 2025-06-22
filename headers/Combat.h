#pragma once
#include "Character.h"
#include "Card.h"




class Combat
{
    enum TURNTYPE : int
    {
        PLAYER = 0,
        ENEMY = 1,
    };

private:
    character player;
    character enemy;

protected:
    int turn = 0;
public:
    Combat() = default;

    void PlayerTurn();
    void EnemyTurn();

    void StartCombat();
    void MakeCardEffect(const Card &card, character &source, character &target);
    void CombatLoop();
    void EndCombat();
    void RunCombat();
};