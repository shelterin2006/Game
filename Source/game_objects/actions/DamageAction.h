#pragma once
#include "IAction.h"
#include "../character/Character.h"
class DamageAction : public IAction {
public:
    int amount;
    string key = "DAMAGE";
    DamageAction() = default;
    ~DamageAction() override = default;
    DamageAction(string name, int dmg) : amount(dmg), key(name) {}
    void Execute( Character& caster, Character& target) override {
        // Thực hiện logic gây sát thương ở đây
        // Ví dụ: target.takeDamage(amount);
        target.attributes.hp -= amount;
        printf("Executed: Dealt %d damage.\n", amount);
    }
    [[nodiscard]] const string& GetAnimationKey() const override {
        return key;
    }
    [[nodiscard]] const int GetValue() const override {
        return amount;
    }
    [[nodiscard]] std::unique_ptr<IAction> clone() const override {
        return std::make_unique<DamageAction>(*this); // Copy constructor
    }
    void printInfo() const override {
        cout << amount << ' ' << key << " | ";
    }
};