#include "pickCard.h"
#include "battleScene.h"
#include "mainMenu.h"
#include "../game_objects/character/CharacterManager.h"

void PickCardScene::onEnter(Game& game) {
    playGame = {1100, 650, 100, 60};
    back = {0, 0, 100, 60};
    random = {0, 650, 100, 60};
    numRandom = 11;
    auto data = std::any_cast<std::string>(game.getSceneData());
    game.player = CharacterManager::getInstance().GetCharacter(data);
    string d = (data == "Sirin" ? "TeRiRi" : "Sirin");
    game.enemy = CharacterManager::getInstance().GetCharacter(d);
    game.player->attributes.randomData();
    game.enemy->attributes.randomData();
    randomDesk(game);
    int da = rnd(1, 5);
    bg = Resource::getInstance().getTexture2D("bg" + to_string(da));
}

void PickCardScene::update(Game& game) {
    if (Utils::isPressed(playGame)) {
        if (chose.size() == 0) return;
        game.switchScene(std::make_unique<BattleScene>());
        return;
    }
    if (Utils::isPressed(back)) {
        game.switchScene(std::make_unique<MainMenuScene>());
        return;
    }
    if (Utils::isPressed(random)) {
        randomDesk(game);
        return;
    }
    for (int i = 0; i < 5; i++) {
        if (Utils::isPressed({point[i].x, point[i].y, 100, 100})) {
            if (deleteChose(i) == false) {
                chose.push_back(i);
            }
        }
    }
}

void PickCardScene::draw(Game& game) {
    DrawTexture(bg, 0, 0, WHITE);
    DrawRectangleRec(back, RED);
    const char *playText = "Back";
    int fontSize = 20;
    int textWidth = MeasureText(playText, fontSize);
    int textX = back.x + (back.width - textWidth) / 2;
    int textY = back.y + (back.height - fontSize) / 2; // căn giữa theo chiều dọc
    DrawText(playText, textX, textY, fontSize, BLACK);
    DrawRectangleRec(playGame, ORANGE);
    DrawRectangleRec(random, BLUE);
    DrawText(("Random " + to_string(numRandom)).c_str(), 10, 650, 20, WHITE);
    const char *Text = "Play";
    textWidth = MeasureText(playText, fontSize);
    textX = playGame.x + (playGame.width - textWidth) / 2;
    textY = playGame.y + (playGame.height - fontSize) / 2; // căn giữa theo chiều dọc
    DrawText(Text, textX, textY, fontSize, BLACK);
    for (int i = 0; i < 5; i++) {
        DeckManager::getInstance().GetCardByID(game.desk1[i])->Draw(point[i], 0.07f);
    }
    int i = 1;
    for (auto x : chose) {
        DrawText(to_string(i).c_str(), point[x].x, point[x].y, 32, RED);
        i++;
    }
}

void PickCardScene::onExit(Game& game) {
    vector<string> send;
    for (const int x : chose) {
        send.push_back(game.desk1[x]);
    }
    game.requestSceneChange(std::make_unique<BattleScene>(), send);
}
bool PickCardScene::deleteChose(int a) {
    auto it = std::find(chose.begin(), chose.end(), a);
    // 2. Kiem tra xem co tim thay khong (it != numbers.end()) roi moi xoa
    if (it != chose.end()) {
        chose.erase(it);
        return true;
    } else return false;
}
void PickCardScene::randomDesk(Game &game) {
    if (numRandom == 0) return;
    numRandom--;
    game.desk1.clear();
    point.clear();
    for (int i = 0; i < 5; i++) {
        string d = DeckManager::getInstance().getRandomCardFomeChar(game.player);
        game.desk1.push_back(d);
        cout << d << ' ' << "aa\n";
        point.push_back({100 + i * 200.0f, 100});
    }
}
