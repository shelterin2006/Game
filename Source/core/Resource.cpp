#include "Resource.h"
#include "Animation.h"
#include "../cards/card.h"

const Texture2D& Resource::getTexture2D(const string& str) {
    if (isValidTexture(textures[str]) == false) {
        TraceLog(LOG_WARNING, "Cannot get Texture2D from: %s", str.c_str());
    }
    return textures[str];
}
const Texture2D& Resource::getTexture2D(const Card& other) {
    return getTexture2D(other.name);
}
const Texture2D& Resource::getTexture2D(const Animation& ani) {
    return getTexture2D(ani.key);
}

void Resource::loadTexture2D() {
    map<int, string> mp;
    mp[1] = "resources/textures/character/";
    mp[2] = "resources/textures/card/";
    for (int i = 1; i <= 2; i++) {
        string currentFolderPath = mp[i];
        std::ifstream folderFile(currentFolderPath + "nameFolder.txt");
        if (!folderFile.is_open()) {
            TraceLog(LOG_ERROR, "Failed to open nameFolder.txt");
        }
        std::string folderName;
        while (std::getline(folderFile, folderName)) {
            if (folderName.empty()) continue; // Bỏ qua các dòng trống
            TraceLog(LOG_INFO, "Processing folder: %s", (currentFolderPath + folderName).c_str());
            std::ifstream pngFile(currentFolderPath + folderName + "/name.txt");
            if (!pngFile.is_open()) {
                TraceLog(LOG_WARNING, "Could not find name.txt in folder: %s", folderName.c_str());
                continue; // Bỏ qua thư mục này và tiếp tục với thư mục tiếp theo
            }
            std::string tex;
            while (std::getline(pngFile, tex)) {
                if (tex.empty()) continue;
                std::string pngPath = currentFolderPath + folderName + "/" + tex + ".png";
                Texture2D a = LoadTexture(pngPath.c_str());
                string name = (i == 1 ? "Char" : "Card");
                name = name + folderName + tex;
                textures[name] = a;
                TraceLog(LOG_INFO, "  - Loaded tex2D: %s", tex.c_str());
                TraceLog(LOG_INFO, "From path: %s", pngPath.c_str());
            }
            pngFile.close();
        }
        folderFile.close();
    }
    textures["bg1"] = LoadTexture("resources/textures/bg/bg1.png");
    textures["bg2"] = LoadTexture("resources/textures/bg/bg2.png");
    textures["bg3"] = LoadTexture("resources/textures/bg/bg3.png");
    textures["bg4"] = LoadTexture("resources/textures/bg/bg4.png");
    textures["bg5"] = LoadTexture("resources/textures/bg/bg5.png");
}