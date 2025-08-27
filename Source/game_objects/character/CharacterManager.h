#pragma once
#include "../../utils/gamedefs.h"
#include "Character.h"

class CharacterManager {
private:
    // Dùng map để quản lý các nhân vật bằng một tên định danh (handle)
    // unique_ptr để tự động quản lý bộ nhớ
    std::map<std::string, std::unique_ptr<Character>> m_characters;
    // Singleton pattern: private constructor
    CharacterManager() = default;
    CharacterManager(const CharacterManager&) = delete;
    CharacterManager operator=(const CharacterManager&) = delete;
public:
    // Hàm để lấy instance duy nhất
    static CharacterManager& getInstance() {
        static CharacterManager instance;
        return instance;
    }
    void loadChar() ;
    // Lấy con trỏ đến nhân vật bằng tên định danh
    Character* GetCharacter(const std::string& handle) {
        return m_characters[handle].get();
    }
    void PrintAll() const;
};