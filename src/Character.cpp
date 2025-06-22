#include "Character.h"


int character::Attack(character& target)
{
    double damage = (baseDamage + effects.buffs[BUFF::POWER]) * ManaAmp;
    if(target.effects.debuffs[DEBUFF::VULNERABLE]-- > 0)
    {
        damage *= 1.5;
    }
    return int(damage);
}

void character::TakeDamage(int damage)
{
    damage -= (int)effects.buffs[BUFF::SHIELD] * ManaAmp; 
    if (damage < 0) damage = 0; 
    currentHealth -= damage;
    if (currentHealth < 0) currentHealth = 0;
}