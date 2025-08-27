#include "card.h"
#include "../game_objects/actions/IAction.h"
#include "../game_objects/actions/DamageAction.h"
#include "../game_objects/actions/HealAction.h"
#include "../utils/Params.h"
void Card::setDataFromParams(const string& path) {
    Params p;
    p.parseParamsFromFile(path);
    int i = 1;
    nameChar = p.getString("Char");
    name = p.getString("name");
    while (true) {
        const string t = "action_" + to_string(i) + "_type";
        if (p.getString(t).empty()) return;
        string f = p.getString(t);
        const string AnimationKey = "action_" + to_string(i) + "_animation_key";
        const string value = "action_" + to_string(i) + "_value";
        if (f == "DAMAGE") {
            actions.push_back(make_unique<DamageAction>(
                p.getString(AnimationKey),
                p.getInt(value)));
        } else if (f == "HEAL") {
            actions.push_back(make_unique<HealAction>(
                p.getString(AnimationKey),
                p.getInt(value)));
        }
        i++;
    }
}
