#pragma once
#include "../utils/gamedefs.h"
// Forward declarations
class Card;
class Animation;

class Resource {
private:
    //fortmat save
    // Card/Char + nameChar + nameTex2D
    map<string, Texture2D> textures;
    vector<string> idTexture2D;
    Resource() = default;
    Resource(const Resource&) = delete;
    Resource operator=(const Resource&) = delete;
public:
    float screenWidth = 1280, screenHeight = 720, fps = 60;
    string title = "CLC game";
    static Resource& getInstance() {
        static Resource instance;
        return instance;
    }
    void loadTexture2D();
    void unloadAllTexture2D() {
        for (auto x : textures) {
            UnloadTexture(x.second);
        }
        textures.clear();
    }
    ~Resource() {
        this->unloadAllTexture2D();
    }
    const Texture2D& getTexture2D(const string& str);
    const Texture2D& getTexture2D(const Card& other);
    const Texture2D& getTexture2D(const Animation& ani);
    void Print() {
        cout << "All tex2d: \n";
        for (auto x : textures) {
            cout << x.first << endl;
        }
        cout << "---------------------\n";
    }
    bool isValidTexture(const Texture2D& tex) {
        return tex.id > 0 && tex.width > 0 && tex.height > 0;
    }
};