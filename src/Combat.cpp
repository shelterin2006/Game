#include "Combat.h"
#include <iostream>

extern int numBuffs = 5;
extern int numDebuffs = 2;

void Combat::PlayerTurn()
{
    int damage = player.Attack(enemy);
    enemy.TakeDamage(damage);
    turn ++; 
}
void Combat::EnemyTurn()
{
    int damage = enemy.Attack(player);
    player.TakeDamage(damage);
    turn ++; 
}

void MakeCardEffect(const Card& card, character& source, character& target)
{
    // Apply buffs
    for (int i = 0; i < numBuffs; ++i)
    {
        source.effects.buffs[i] += card.effects.buffs[i];
    }
    // Apply debuffs
    for (int i = 0; i < numDebuffs; ++i)
    {
        target.effects.debuffs[i] += card.effects.debuffs[i];
    }
    
}

void Combat::StartCombat()
{
    player = character("Hero", "The brave hero", 100, 10.0, 1);
    enemy = character("Goblin", "A sneaky goblin", 100, 10.0, 1);
    player.Deck.push_back(Card1());
    enemy.Deck.push_back(Card2());
    turn = 0;
}

void Combat::CombatLoop()
{
    while (player.currentHealth && enemy.currentHealth)
    {
        std::cout <<"_______________________________________" << std::endl;
        std::cout << "Turn: " << ((turn % 2 == PLAYER) ? "Player" : "Enemy") << std::endl;
        if (turn % 2 == PLAYER)
        {
            MakeCardEffect(player.Deck[turn % player.Deck.size()], player, enemy);
            PlayerTurn();   
        }
        else
        {   
            MakeCardEffect(enemy.Deck[turn % enemy.Deck.size()], enemy, player);
            EnemyTurn();
        } 
        std::cout << "Player Health: " << player.currentHealth << ", Enemy Health: " << enemy.currentHealth << std::endl;
        std::cout <<"_______________________________________" << std::endl;
        
    }
}

void Combat::EndCombat()
{
    if (player.currentHealth > 0)
    {
        std::cout << "Player wins!" << std::endl;
    }
    else
    {
        std::cout << "Enemy wins!" << std::endl;
    } 
}
void Combat::RunCombat()
{
    StartCombat();
    CombatLoop();
    EndCombat();
}



