#include "battleScene.h"
#include "../cards/DeckManager.h"
#include "../game_objects/actions/IAction.h"
BattleScene::BattleScene() : currentState(BattleState::START_BATTLE) {}

// class QueuedAction
QueuedAction::QueuedAction(std::unique_ptr<IAction> act, string src, string tgt, int a)
        : action(std::move(act)), caster(src), target(tgt), idCard(a) {}

QueuedAction::QueuedAction(const QueuedAction& other)
        : action(other.action ? other.action->clone() : nullptr),
          caster(other.caster),
          target(other.target), idCard(other.idCard) {}
QueuedAction& QueuedAction::operator=(const QueuedAction& other) {
    if (this != &other) {
        action = other.action ? other.action->clone() : nullptr;
        caster = other.caster;
        target = other.target; idCard = other.idCard;
    }
    return *this;
}
//---------------------------

void BattleScene::SetupCard(Game &game) {
    // Lấy dữ liệu từ Game
    const std::any& data = game.getSceneData();
    // Kiểm tra xem dữ liệu có tồn tại không và có đúng kiểu không
    if (data.has_value() && data.type() == typeid(std::vector<std::string>)) {
        try {
            // Ép kiểu dữ liệu về đúng kiểu mong muốn
            auto m_receivedData = std::any_cast<std::vector<std::string> >(data);
            // Bây giờ bạn có thể sử dụng dữ liệu
            std::cout << "Received data: ";
            for (const auto& str : m_receivedData) {
                std::cout << str << " ";
                game.desk1.push_back(str);
            }
            std::cout << std::endl;
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error casting scene data: " << e.what() << std::endl;
        }
    } else {
        std::cout << "No data or wrong data type received." << std::endl;
    }
    for (int i = 0; i < game.desk1.size(); i++) {
        game.desk2.push_back(DeckManager::getInstance().getRandomCardFomeChar(game.enemy));
    }
    //creat id cards
    int j = 2;
    for (int i = 0; i < game.desk1.size(); i++) {
        id1.push_back(j++);
        id2.push_back(j++);
    }
}

void BattleScene::SetupAnimation(Game &game) {
    game.player->setPointAuto(true);
    game.enemy->setPointAuto(false);
    game.player->ReturnToIdle();
    game.enemy->ReturnToIdle();
    game.player->getAnimation()->Play();
    game.enemy->getAnimation()->Play();
}

void BattleScene::BuildBattleQueue(Game& game) {
    actionQueue.clear(); // Sử dụng biến thành viên m_actionQueue
    size_t maxTurns = std::max(game.desk1.size(), game.desk2.size());
    cout << "desk 1 size: " << game.desk1.size() << endl;
    cout << "desk 2 size: " << game.desk2.size() << endl;
    for (size_t i = 0; i < maxTurns; i++) {
        cout << "i set :" << i << endl;
        // Lượt của Player
        DeckManager &d = DeckManager::getInstance();
        if (i < game.desk1.size()) {
            Card* card = DeckManager::getInstance().GetCardByID(game.desk1[i]);
            for (const auto& actionTemplate : card->actions) {
                actionQueue.push_back({ actionTemplate->clone(),
                    "player", "enemy", id1[i] });
            }
        }
        // Lượt của Enemy
        if (i < game.desk2.size()) {
            Card* card = DeckManager::getInstance().GetCardByID(game.desk2[i]);
            for (const auto& actionTemplate : card->actions) {
                actionQueue.push_back({ actionTemplate->clone(),
                    "enemy", "player", id2[i]});
            }
        }
    }
    cout << "Queue " << actionQueue.size() << endl;
    for (QueuedAction& x : actionQueue) {
        cout << x.action->GetAnimationKey() << endl;
    }
    actionQueue_2 = actionQueue;
}

void BattleScene::onEnter(Game& game) {
    back = {0, 0, 100, 60};
    int da = rnd(1, 5);
    bg = Resource::getInstance().getTexture2D("bg" + to_string(da));
    game.desk1.clear();
    game.desk2.clear();
    SetupCard(game);
    BuildBattleQueue(game);
    SetupAnimation(game);
    currentState = BattleState::START_BATTLE;
}

void BattleScene::update(Game& game) {
    if (Utils::isPressed(back)) {
        game.switchScene(std::make_unique<MainMenuScene>());
        return;
    }
    game.player->Update();
    game.enemy->Update();

    // MÁY TRẠNG THÁI CỦA TRẬN ĐẤU
    switch (currentState) {
        case BattleState::START_BATTLE: {
            // Có thể thêm một đoạn delay ngắn hoặc animation "Ready... Fight!"
            // Sau khi xong, chuyển sang xử lý hành động đầu tiên
            currentState = BattleState::PROCESS_NEXT_ACTION;
            break;
        }
        case BattleState::PROCESS_NEXT_ACTION: {
            // Nếu không còn hành động nào trong hàng đợi -> trận đấu kết thúc
            if (actionQueue.empty()) {
                actionQueue = actionQueue_2;
                break;
            }
            // Lấy hành động tiếp theo
            QueuedAction& currentAction = actionQueue[0];
            cardPlay = currentAction.idCard;
            // 2. Yêu cầu nhân vật thực hiện animation
            if (currentAction.caster == "player") {
                game.player->currentAnimation = currentAction.action->GetAnimationKey();
                currentAction.action->Execute(*game.player, *game.enemy);
                game.player->getAnimation()->Play();
                // if (game.player->currentAnimation == "")
                if (game.player->currentAnimation.find("ATTACK") != string::npos)
                    game.player->MoveTo(game.enemy->point, 0.1f * 7);
            } else {
                game.enemy->currentAnimation = currentAction.action->GetAnimationKey();
                currentAction.action->Execute(*game.enemy, *game.player);
                game.enemy->getAnimation()->Play();
                if (game.enemy->currentAnimation.find("ATTACK") != string::npos)
                    game.enemy->MoveTo(game.enemy->point, 0.1f * 7);
            }
            // 3. Chuyển sang trạng thái đợi animation
            currentState = BattleState::ANIMATING_ACTION;
            break;
        }
        case BattleState::ANIMATING_ACTION: {
            QueuedAction& currentAction = actionQueue.front();
            string animationKey = currentAction.action->GetAnimationKey();
            // Chờ cho đến khi animation của người thực hiện kết thúc
            Character *caster = (currentAction.caster == "player" ? game.player : game.enemy);
            if (caster->getAnimation()->isPlaying == false) {
                // Khi animation xong, đưa nhân vật về trạng thái nghỉ
                caster->ReturnToIdle();
                // Xóa hành động đã hoàn thành khỏi hàng đợi
                actionQueue.erase(actionQueue.begin());
                // Kiểm tra điều kiện thắng/thua ngay lập tức
                if (game.player->getHP() <= 0 || game.enemy->getHP() <= 0) {
                    currentState = BattleState::BATTLE_OVER;
                } else {
                    // Nếu chưa ai thua, quay lại để xử lý hành động tiếp theo
                    currentState = BattleState::BREAKTIME;
                }
            }
            break;
        }
        case BattleState::BREAKTIME: {
            game.player->resetPoint();
            game.enemy->resetPoint();
            timeerrr += GetFrameTime();
            if (timeerrr > 0.7f) {
                timeerrr = 0.0f;
                currentState = BattleState::PROCESS_NEXT_ACTION;
            }
            break;
        }
        case BattleState::BATTLE_OVER: {
            if (GetKeyPressed() != 0) {
                game.switchScene(std::make_unique<MainMenuScene>());
            }
            break;
        }

        default:
            // Các trạng thái khác (nếu có)
            break;
    }
}

void BattleScene::draw(Game& game) {
    DrawTexture(bg, 0, 0, WHITE);
    game.player->Draw();
    game.enemy->Draw();
    DrawRectangleRec(back, RED);
    DrawText("Back", 10, 10, 20, WHITE);
    DeckManager &d = DeckManager::getInstance();
    for (int i = 0; i < game.desk1.size(); i++) {
        float y = (id1[i] == cardPlay ? -100 : 0);
        DeckManager::getInstance().GetCardByID(game.desk1[i])->Draw
            ({100 + 50.0f * i, 500 + y}, 0.07f);
    }
    for (int i = 0; i < game.desk2.size(); i++) {
        float y = (id2[i] == cardPlay ? -100 : 0);
        DeckManager::getInstance().GetCardByID(game.desk2[i])->Draw
            ({1000 + 50.0f * i, 500 + y}, 0.07f);
    }

    // 2. Vẽ giao diện người dùng (thanh máu, tên,...)
    // Player UI
    DrawRectangle(40, 40, 300, 30, GRAY);
    DrawRectangle(40, 40, 300 * (game.player->getHP() / game.player->getMAXHP()), 30, GREEN);
    DrawRectangleLines(40, 40, 300, 30, BLACK);
    DrawText(TextFormat("Player HP: %d", (int)game.player->getHP()), 50, 45, 20, WHITE);

    // Enemy UI
    DrawRectangle(GetScreenWidth() - 340, 40, 300, 30, GRAY);
    DrawRectangle(GetScreenWidth() - 340, 40, 300 * (game.enemy->getHP() / game.enemy->getMAXHP()), 30, RED);
    DrawRectangleLines(GetScreenWidth() - 340, 40, 300, 30, BLACK);
    DrawText(TextFormat("Enemy HP: %d", (int)game.enemy->getHP()), GetScreenWidth() - 330, 45, 20, WHITE);

    // 3. Nếu trận đấu kết thúc, vẽ màn hình kết quả
    if (currentState == BattleState::BATTLE_OVER) {
        // Vẽ một lớp nền mờ
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.8f));

        // Xác định văn bản kết quả
        const char* resultText = "";
        if (game.player->getHP() > 0) {
            resultText = "VICTORY";
        } else {
            resultText = "DEFEAT";
        }

        // Tính toán vị trí để căn giữa và vẽ
        Vector2 textSize = MeasureTextEx(GetFontDefault(), resultText, 80, 2);
        DrawText(resultText, (GetScreenWidth() - textSize.x) / 2, GetScreenHeight() / 2 - 60, 80, GOLD);

        const char* promptText = "Press Any Key to continue";
        textSize = MeasureTextEx(GetFontDefault(), promptText, 20, 1);
        DrawText(promptText, (GetScreenWidth() - textSize.x) / 2, GetScreenHeight() / 2 + 40, 20, LIGHTGRAY);
    }
}

void BattleScene::onExit(Game& game) {
    // Dọn dẹp nếu cần
}

