#pragma once
#include "../utils/gamedefs.h"
#include "../game_objects//character/Character.h"

typedef enum  {
    LOGO, CREDITS, TITLE, MAP, GAMEPLAY, ENDING, PICKCATD
}GameScreen;

class Scene;

class Game {
public:
    Character *player, *enemy;
    vector<string> desk1;
    vector<string> desk2;

    // Biến để quản lý việc chuyển scene một cách an toàn
    std::unique_ptr<Scene> m_nextScene;
    std::any m_sceneData; // Nơi lưu trữ dữ liệu để truyền đi
    bool m_isChangingScene = false;
private:
    std::unique_ptr<Scene> currentScene;
    bool shouldClose = false;
public:
    ~Game();
    void run();
    void switchScene(std::unique_ptr<Scene> newScene);
    void closeGame() { shouldClose = true; }
    void requestSceneChange(std::unique_ptr<Scene> newScene, std::any data = std::any());
    [[nodiscard]] const std::any& getSceneData() const {
        return m_sceneData;
    }
};
class Scene {
public:
    virtual ~Scene() = default;
    virtual void onEnter(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void draw(Game& game) = 0;
    virtual void onExit(Game& game) = 0;
};