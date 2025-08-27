#pragma once
#include "../utils/gamedefs.h"
#include "../game_objects/actions/IAction.h"
#include "../core/Resource.h"

class Card {
public:
    string nameChar, name;
    vector<unique_ptr<IAction>> actions;
    Card() {
        name = "";
    }
    Card(string nameCard, string namechar) {
        name = std::move(nameCard);
        nameChar = std::move(namechar);
    }
    void AddAction(unique_ptr<IAction> action) {
        actions.push_back(std::move(action));
    }
    void Draw(const Vector2& point, float scale) const {
        const Texture2D& texture = Resource::getInstance().getTexture2D(*this);
        Rectangle sourceRec = { 0.0f, 0.0f,
            (float)texture.width, (float)texture.height };
        Rectangle destRec = {point.x,point.y,
            (float)texture.width * scale,
            (float)texture.height * scale
        };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(
            texture,      // Texture cần vẽ
            sourceRec,    // Phần nào của texture để vẽ
            destRec,      // Vẽ ở đâu và kích thước nào trên màn hình
            origin,       // Điểm gốc để xoay
            0.0f,         // Góc xoay (rotation)
            WHITE         // Màu sắc (tint)
        );
    }
    void setDataFromParams(const string& path);
    void printInfo() {
        cout << nameChar << ' ' << name << ' ';
        for (auto &x : actions) {
            x->printInfo();
        }
    }
};
