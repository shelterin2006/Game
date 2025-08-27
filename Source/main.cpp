#include "cards/DeckManager.h"
#include "core/scene.h"
#include "game_objects/character/Character.h"
#include "scenes/mainMenu.h"
#include "scenes/credits.h"
#include "core/Resource.h"
#include "scenes/pickCard.h"
#include "game_objects/character/CharacterManager.h"

int main()
{
    Game game;
    Resource &rs = Resource::getInstance();
    InitWindow(rs.screenWidth, rs.screenHeight, rs.title.c_str());
    SetTargetFPS(rs.fps);
    rs.loadTexture2D();
    rs.Print();
    DeckManager::getInstance().InitializeDeck();
    DeckManager::getInstance().PrintAll();
    CharacterManager::getInstance().loadChar();
    CharacterManager::getInstance().PrintAll();
    game.switchScene(std::make_unique<MainMenuScene>());
    game.run();
    return 0;
}
