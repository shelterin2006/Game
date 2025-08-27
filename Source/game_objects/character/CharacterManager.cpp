#include "CharacterManager.h"
#include "Character.h"

void CharacterManager::loadChar() {
    string currentFolderPath = "resources/data/character/";
    std::ifstream folderFile(currentFolderPath + "nameFolder.txt");
    if (!folderFile.is_open()) {
        TraceLog(LOG_ERROR, "Failed to open nameFolder.txt");
    }
    std::string folderName;
    cout << "Data from loadChar character manager:\n";
    while (std::getline(folderFile, folderName)) {
        if (folderName.empty()) continue; // Bỏ qua các dòng trống
        TraceLog(LOG_INFO, "Processing folder: %s", (currentFolderPath + folderName).c_str());
        std::ifstream pngFile(currentFolderPath + folderName + "/name.txt");
        if (!pngFile.is_open()) {
            TraceLog(LOG_WARNING, "Could not find name.txt in folder: %s", folderName.c_str());
            continue; // Bỏ qua thư mục này và tiếp tục với thư mục tiếp theo
        }
        std::string tex;
        m_characters[folderName] = make_unique<Character>();
        m_characters[folderName]->name = folderName;
        cout << folderName << ' ';
        while (std::getline(pngFile, tex)) {
            if (tex.empty()) continue;
            std::string pngPath = currentFolderPath + folderName + "/" + tex + ".txt";
            int frame = 3;
            bool d = (tex == "IDLE" ? true : false);
            string t = "Char" + folderName + tex;
            m_characters[folderName]->animations[t] =
                make_unique<Animation>(t, frame, 0.25f, d);
            cout << "a: " << t << '\n';
        } cout << endl;
        pngFile.close();
    }
    cout << "------------------------\n";
    folderFile.close();
}

void CharacterManager::PrintAll() const {
    cout << "-----------------------------------------\n";
    cout <<"Print all from character manager:\n";
    for (auto& [key, value] : m_characters) {
        const Character* character = value.get(); // Lấy raw pointer
        cout << key << ' ';
        character->PrintAllCard();
        cout << endl;
    }
    cout << "------------------------\n";
}