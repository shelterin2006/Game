#pragma once
#include "../../utils/gamedefs.h"
#include "../../core/Animation.h"

// Forward declaration
class DeckManager;

struct attributesCharacter {
    float MAXHP;
    float hp, def, attack;
    float mana;
    attributesCharacter() = default;
    attributesCharacter(int HP, int DEF, int ATTACK, int MANA):
    MAXHP(HP), hp(HP), def(DEF), attack(ATTACK), mana(MANA) {}
    void randomData() {
        MAXHP = hp = rnd(10, 30);
        def = attack = mana = 1.0f;
    }
};

class Character {
private:
    bool m_isMoving = false;
    Vector2 m_startPos = {};
    Vector2 m_endPos = {};
    float m_moveTimer = 0.0f;
    float m_moveDuration = 0.0f;
public:
    string name;
    attributesCharacter attributes;
    Vector2 point = {};
    Vector2 rootPoint = {};
    bool isFlipped;
    string currentAnimation = "IDLE"; // Lưu key của animation mặc định
    std::map<std::string, std::unique_ptr<Animation>> animations;
    //-------------------------------
    // --- HÀM DI CHUYỂN DUY NHẤT ---
    Character(): attributes(), isFlipped(false) {
        animations.clear();
    }
    void setPointAuto(bool player) {
        if (player) {
            point = {100, 100};
            rootPoint = point;
            isFlipped = false;
        } else {
            point = {1000, 100};
            rootPoint = point;
            isFlipped = true;
        }
    }
    void setValue(Vector2 point, bool flip) {
        rootPoint = this->point = point;
        isFlipped = flip;
    }
    void MoveTo(Vector2 targetPosition, float duration) {
        // Nếu đang di chuyển rồi thì không làm gì cả
        if (m_isMoving) return;
        // Thiết lập các thông số cho việc di chuyển
        m_isMoving = true;
        m_startPos = this->point;
        m_endPos = targetPosition;
        m_moveDuration = duration;
        m_moveTimer = 0.0f; // Reset bộ đếm giờ
    }
    void Update() {
        // 1. Cập nhật animation (như cũ)
        if (animations.count(currentAnimation)) {
            animations[currentAnimation]->Update();
        }
        // 2. Xử lý logic di chuyển nếu đang di chuyển
        if (m_isMoving) {
            m_moveTimer += GetFrameTime();
            // Tính toán tiến trình (từ 0.0 đến 1.0)
            float progress = m_moveTimer / m_moveDuration;
            if (progress >= 1.0f) {
                // Nếu đã hoàn thành
                progress = 1.0f;
                m_isMoving = false; // Dừng di chuyển
            }
            // Dùng Lerp để cập nhật vị trí một cách mượt mà
            this->point = Vector2Lerp(m_startPos, m_endPos, progress);
        }
    }
    void resetPoint(){this->point = rootPoint;};
    void Draw() {
        Animation* currentAnim = animations[currentAnimation].get();
        if (!currentAnim) {
            cout <<"Error " << currentAnim << ' ' << currentAnimation << endl;
            return;
        }
        Rectangle sourceRec = currentAnim->frameRec;
        sourceRec.width = (isFlipped ? -sourceRec.width : sourceRec.width);
        float scale = 0.2f;
        Rectangle destRec = { point.x,point.y,
            std::abs(sourceRec.width) * scale,
            sourceRec.height * scale
        };
        Vector2 origin = { 0.0f, 0.0f }; // Vẽ từ góc trên bên trái
        // 5. Vẽ bằng DrawTexturePro
        DrawTexturePro(currentAnim->spritesheet, sourceRec,
                       destRec,origin, 0.0f, WHITE);
    }
    [[nodiscard]] float getHP() const{return attributes.hp;}
    [[nodiscard]] float getMAXHP() const{return attributes.MAXHP;}
    void ReturnToIdle() {
        currentAnimation = "Char" + name + "IDLE";
    }
    Animation* getAnimation() {
        return animations[currentAnimation].get();
    }
    //Debug space
    void PrintAllCard() const {
        cout << name << ' ';
        cout << "animation character " << name << " : ";
        for (const auto& x : animations) {
            cout << x.first << ' ';
        }
    }
};