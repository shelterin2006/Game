#pragma once

#include <string>
#include "Effect.h"

class Card
{
protected:
    int level;
    int manaCost;

public:
    std::string name;
    std::string description;
    Effect effects;
    void levelUp();
};