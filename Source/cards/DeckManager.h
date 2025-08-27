#pragma once
#include "../utils/gamedefs.h"
#include "card.h"

// Forward declarations
class DamageAction;
class HealAction;

class DeckManager {
private:
    // Dùng map để truy cập nhanh bằng ID (tên thẻ bài)
    std::map<std::string, std::unique_ptr<Card>> allCards;
    DeckManager() = default;
    DeckManager(const Resource&) = delete;
    DeckManager operator=(const Resource&) = delete;
public:
    static DeckManager& getInstance() {
        static DeckManager instance; return instance;
    }
    void InitializeDeck();
    // Hàm quan trọng: Lấy con trỏ đến lá bài bằng ID
    Card* GetCardByID(const std::string& cardID) const;
    [[nodiscard]] string getRandomCardID() const;
    [[nodiscard]] string getRandomCardFomeChar(Character *) const;
    // Lấy danh sách tất cả các ID thẻ bài có sẵn
    std::vector<std::string> GetAllCardIDs() const;
    [[nodiscard]] int size() const;
    void PrintAll() const;
    vector<Card*> getAllCardfromChar(Character *) const;
};