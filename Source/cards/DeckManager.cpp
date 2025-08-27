#include "DeckManager.h"
#include "../game_objects/actions/IAction.h"
#include "../game_objects/actions/DamageAction.h"
#include "../game_objects/actions/HealAction.h"
#include "../utils/Params.h"

void DeckManager::InitializeDeck() {
    string currentFolderPath = "resources/data/card/";
    std::ifstream folderFile(currentFolderPath + "nameFolder.txt");
    if (!folderFile.is_open()) {
        TraceLog(LOG_ERROR, "Desk Failed to open nameFolder.txt");
    }
    std::string folderName;
    while (std::getline(folderFile, folderName)) {
        if (folderName.empty()) continue; // Bỏ qua các dòng trống
        TraceLog(LOG_INFO, "Processing folder: %s", (currentFolderPath + folderName).c_str());
        string path = currentFolderPath + folderName + "/";
        std::ifstream pngFile(path + "name.txt");
        if (!pngFile.is_open()) {
            TraceLog(LOG_WARNING, "Could not find name.txt in folder: %s", folderName.c_str());
            continue; // Bỏ qua thư mục này và tiếp tục với thư mục tiếp theo
        }
        std::string tex;
        while (std::getline(pngFile, tex)) {
            if (tex.empty()) continue;
            string name = "Card" + folderName + tex;
            allCards[name] = make_unique<Card>();
            string txtPath = path + tex + ".txt";
            allCards[name]->setDataFromParams(txtPath);
        } cout << endl;
        pngFile.close();
    }
    folderFile.close();
    cout << "Loaded " << allCards.size() << " unique cards into the library.\n";
}

Card* DeckManager::GetCardByID(const std::string& cardID) const {
    auto it = allCards.find(cardID);
    if (it != allCards.end()) {
        return it->second.get(); // Trả về con trỏ thô
    }
    TraceLog(LOG_WARNING, "DECK_MANAGER: Requested card with unknown ID: %s", cardID.c_str());
    return nullptr;
}

string DeckManager::getRandomCardID() const {
    int i = rnd(0, allCards.size() - 1);
    auto it = allCards.begin();
    advance(it, i);
    return it->first;
}

std::vector<std::string> DeckManager::GetAllCardIDs() const {
    std::vector<std::string> ids;
    ids.reserve(allCards.size());
    for (const auto& pair : allCards) {
        ids.push_back(pair.first);
    }
    return ids;
}

int DeckManager::size() const {
    return static_cast<int>(allCards.size());
}

void DeckManager::PrintAll() const {
    cout << "Print all card from desk manager: " << allCards.size() << "\n";
    for (const auto& x : allCards) {
        cout << x.first << ' ';
            x.second->printInfo(); cout << endl;
    }
    cout << "----------------------------\n";
}

vector<Card*> DeckManager::getAllCardfromChar(Character *other) const {
    vector<Card*> ans;
    string a = "Card" + other->name;
    for (auto& key : allCards) {
        cout << a << endl;
        if (key.first.find(a) != std::string::npos) {
            ans.push_back(key.second.get());
            cout << key.first << endl;
        }
    }
    return ans;
}
string DeckManager::getRandomCardFomeChar(Character *other) const {
    string t = "Card" + other->name;
    vector<Card*> ans = getAllCardfromChar(other);
    if (ans.size() == 0) return "CardTeRiRiHEAL";
    if (!ans[rnd(0, ans.size() - 1)]) {
        return "CardTeRiRiHEAL";
    }
    return ans[rnd(0, ans.size() - 1)]->name;
}

