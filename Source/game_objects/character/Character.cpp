#include "Character.h"
#include "../../cards/DeckManager.h"

void Character::PrintAllCard() const {
    const vector<Card*> a = DeckManager::getInstance().getAllCardfromChar(name);
    cout << "All card from char " << name << " :\n";
    for (const auto ca : a) {
        cout << ca->nameChar << ' ' << ca->name << endl;
    }
}
