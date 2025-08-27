#pragma once
#include "../../utils/gamedefs.h"

class Character;

class IAction {
public:
    virtual ~IAction() = default;
    // "Hợp đồng": Mọi hành động phải có khả năng tự thực thi.
    virtual void Execute(Character& caster, Character& target) = 0;

    // "Hợp đồng" nhân bản: Để sao chép hành động từ thẻ bài vào hàng đợi
    // virtual std::unique_ptr<IAction> Clone() const = 0;
    [[nodiscard]] virtual const std::string& GetAnimationKey() const = 0;
    [[nodiscard]] virtual const int GetValue() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IAction> clone() const = 0;
    virtual void printInfo() const = 0;
};