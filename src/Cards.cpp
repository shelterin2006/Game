#include "Card.h"

class Card1 : public Card
{
public:
    Card1() {
        name = "Card1";
        description = "This is Card 1";
        level = 1;
        manaCost = 2;
        effects.buffs[BUFF::POWER] = 1; // Example buff
    }
};

class Card2 : public Card
{
public:
    Card2() {
        name = "Card2";
        description = "This is Card 2";
        level = 1;
        manaCost = 3;
        // effects.buffs[BUFF::HEAL] = 10; // Example buff
        effects.debuffs[DEBUFF::VULNERABLE] = 2; // Example debuff
    }
};