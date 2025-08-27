#pragma once
#include "IAction.h"
#include "../character/Character.h"
class HealAction : public IAction {
private:
    int amount;
    string key = "HEAL";
public:
    HealAction() = default;
    ~HealAction() override {
    }
    HealAction(string name, int shield) : amount(shield), key(name) {}
    void Execute( Character& caster, Character& target) override {
        // Thực hiện logic tạo khiên ở đây
        // Ví dụ: source.addShield(amount);
        caster.attributes.hp = min(caster.attributes.MAXHP, caster.attributes.hp + amount);
        printf("Executed: Gained %d heal.\n", amount);
    }
    [[nodiscard]] const string& GetAnimationKey() const override {
        return key;
    }
    [[nodiscard]] const int GetValue() const override {
        return amount;
    }
    [[nodiscard]] std::unique_ptr<IAction> clone() const override {
        return std::make_unique<HealAction>(*this); // Copy constructor
    }
    void printInfo() const override {
        cout << amount << ' ' << key << " | ";
    }
};