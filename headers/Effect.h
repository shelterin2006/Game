#pragma once 

#include <vector>

enum BUFF : int
{
    MANA = 0,
    HEAL = 1,
    POWER = 2,
    SHIELD = 3,
    LUCKY_COIN = 4,
};
enum DEBUFF : int
{
    TOXIC = 0,
    VULNERABLE = 1,
};

class Effect
{
    public:
    Effect() = default;
    std::vector<int> buffs = std::vector<int>(5, 0); // Initialize buffs with 5 types
    std::vector<int> debuffs = std::vector<int>(2, 0); // Initialize debuffs with 2 types
};