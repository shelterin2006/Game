#include "scene.h"

void Game::run() {
    while (!WindowShouldClose() && !shouldClose) {
        if (currentScene) {
            currentScene->update(*this);
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (currentScene) {
            currentScene->draw(*this);
        }
        EndDrawing();
    }
}

Game::~Game() {
    if (currentScene) {
        currentScene->onExit(*this);
    }
    // Window cleanup is now handled in main()
}

void Game::switchScene(std::unique_ptr<Scene> newScene) {
    if (currentScene) {
        currentScene->onExit(*this);
    }
    currentScene = std::move(newScene);
    if (currentScene) {
        currentScene->onEnter(*this);
    }
    // 4. Reset trạng thái
    m_isChangingScene = false;
    m_sceneData.reset(); // Xóa dữ liệu cũ sau khi đã truyền
}

void Game::requestSceneChange(std::unique_ptr<Scene> newScene, std::any data) {
    if (m_isChangingScene == false) {
        m_isChangingScene = true;
        m_nextScene = std::move(newScene);
        m_sceneData = std::move(data);
    }
}