#pragma once 

#include "Card.h"
#include "Cards.cpp"
#include "Effect.h"

class character
{  
    std::string name;
    std::string description;
    int maxHealth;
    double ManaAmp;
    int baseDamage;
    public:
        int currentHealth;
        std::vector<Card> Deck;
        Effect effects;
    public:
        character() = default;
        character(std::string name, std::string description, int maxHealth, double ManaAmp, int damage): 
            name(name), description(description), maxHealth(maxHealth), ManaAmp(ManaAmp), baseDamage(damage) {currentHealth = maxHealth;}
        int Attack(character& target);
        void TakeDamage(int damage);
        // void Movement();
};