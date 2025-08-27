classDiagram
%% ========================================
%% ENUMS & STRUCTS
%% ========================================
class GameScreen {
<<enumeration>>
LOGO
CREDITS
TITLE
MAP
GAMEPLAY
ENDING
PICKCARD
}

class BattleState {
<<enumeration>>
START_BATTLE
PROCESS_NEXT_ACTION
ENEMY_TURN
BATTLE_OVER
ANIMATING_ACTION
BREAKTIME
}

class QueuedAction {
<<struct>>
+IAction* action
+string caster
+string target
+int idCard
+QueuedAction(IAction*, string, string, int)
+QueuedAction(const QueuedAction&)
+QueuedAction& operator=(const QueuedAction&)
}

class attributesCharacter {
<<struct>>
+float MAXHP
+float hp
+float def
+float attack
+float mana
+attributesCharacter()
+attributesCharacter(int, int, int, int)
+randomData() void
}

%% ========================================
%% CORE GAME SYSTEM
%% ========================================
class Game {
-Character* player
-Character* enemy
-vector~string~ deck1
-vector~string~ deck2
-Scene* currentScene
-Scene* nextScene
-any sceneData
-bool isChangingScene
-bool shouldClose
+~Game()
+run() void
+switchScene(Scene*) void
+closeGame() void
+requestSceneChange(Scene*, any) void
+getSceneData() const any&
}

%% ========================================
%% SCENE SYSTEM
%% ========================================
class Scene {
<<abstract>>
+~Scene()
+onEnter(Game&) void
+update(Game&) void
+draw(Game&) void
+onExit(Game&) void
}

class Credits {
-Rectangle back
-Texture2D bg
+Credits()
+~Credits()
+onEnter(Game&) void
+update(Game&) void
+draw(Game&) void
+onExit(Game&) void
}

class MainMenuScene {
+MainMenuScene()
+~MainMenuScene()
+onEnter(Game&) void
+update(Game&) void
+draw(Game&) void
+onExit(Game&) void
}

class BattleScene {
-BattleState currentState
-vector~QueuedAction~ actionQueue
-vector~QueuedAction~ actionQueue2
-Rectangle back
-Texture2D bg
+int cardPlay
+float timeerrr
+vector~int~ id1
+vector~int~ id2
+BattleScene()
+onEnter(Game&) void
+update(Game&) void
+draw(Game&) void
+onExit(Game&) void
+BuildBattleQueue(Game&) void
+SetupCard(Game&) void
+SetupAnimation(Game&) void
}

class ChoseChar {
+ChoseChar()
+~ChoseChar()
+onEnter(Game&) void
+update(Game&) void
+draw(Game&) void
+onExit(Game&) void
}

class PickCard {
+PickCard()
+~PickCard()
+onEnter(Game&) void
+update(Game&) void
+draw(Game&) void
+onExit(Game&) void
}

%% ========================================
%% CHARACTER SYSTEM
%% ========================================
class CharacterManager {
-map~string, Character*~ characters
-CharacterManager()
-CharacterManager(const CharacterManager&)
-CharacterManager operator=(const CharacterManager&)
+getInstance() CharacterManager&
+loadChar() void
+GetCharacter(string) Character*
+PrintAll() void
}

class Character {
-bool isMoving
-Vector2 startPos
-Vector2 endPos
-float moveTimer
-float moveDuration
+string name
+attributesCharacter attributes
+Vector2 point
+Vector2 rootPoint
+bool isFlipped
+string currentAnimation
+map~string, Animation*~ animations
+Character()
+setPointAuto(bool) void
+setValue(Vector2, bool) void
+MoveTo(Vector2, float) void
+Update() void
+resetPoint() void
+Draw() void
+getHP() float
+getMAXHP() float
+ReturnToIdle() void
+getAnimation() Animation*
+PrintAllCard() void
}

%% ========================================
%% ANIMATION SYSTEM
%% ========================================
class Animation {
+string key
+Texture2D spritesheet
+int frameCount
+Rectangle frameRec
+float frameTime
+bool loop
+float impactTime
+bool isPlaying
+int currentFrame
+float frameTimer
+Animation()
+Animation(string, int, float, bool, float)
+Update() void
+Play() void
+Pause() void
+Stop() void
}

%% ========================================
%% CARD SYSTEM
%% ========================================
class Card {
+string nameChar
+string name
+vector~IAction*~ actions
+Card()
+Card(string, string)
+AddAction(IAction*) void
+Draw(Vector2, float) void
+setDataFromParams(string) void
+printInfo() void
}

class IAction {
<<interface>>
+~IAction()
+Execute(Character&, Character&) void
+GetAnimationKey() string
+GetValue() int
+clone() IAction*
+printInfo() void
}

class DamageAction {
+int amount
+string key
+DamageAction()
+~DamageAction()
+DamageAction(string, int)
+Execute(Character&, Character&) void
+GetAnimationKey() string
+GetValue() int
+clone() IAction*
+printInfo() void
}

class HealAction {
-int amount
-string key
+HealAction()
+~HealAction()
+HealAction(string, int)
+Execute(Character&, Character&) void
+GetAnimationKey() string
+GetValue() int
+clone() IAction*
+printInfo() void
}

%% ========================================
%% RESOURCE MANAGEMENT
%% ========================================
class Resource {
-map~string, Texture2D~ textures
-vector~string~ textureIDs
+float screenWidth
+float screenHeight
+float fps
+string title
-Resource()
-Resource(const Resource&)
-Resource operator=(const Resource&)
+getInstance() Resource&
+loadTexture2D() void
+unloadAllTexture2D() void
+~Resource()
+getTexture2D(string) Texture2D&
+getTexture2D(Card) Texture2D&
+getTexture2D(Animation) Texture2D&
+Print() void
+isValidTexture(Texture2D) bool
}

class DeckManager {
-map~string, Card*~ allCards
-DeckManager()
-DeckManager(const DeckManager&)
-DeckManager operator=(const DeckManager&)
+getInstance() DeckManager&
+InitializeDeck() void
+GetCardByID(string) Card*
+getRandomCardID() string
+getRandomCardFomeChar(Character*) string
+GetAllCardIDs() vector~string~
+size() int
+PrintAll() void
+getAllCardfromChar(Character*) vector~Card*~
}

%% ========================================
%% UTILITIES
%% ========================================
class Params {
+map~string, string~ params
+getInt(string, int) int
+getString(string, string) string
+parseParams(string) void
+parseParamsFromFile(string) bool
}

%% ========================================
%% RELATIONSHIPS
%% ========================================
%% Core & Scenes
Game o-- Scene : manages
Scene <|-- Credits
Scene <|-- MainMenuScene
Scene <|-- BattleScene
Scene <|-- ChoseChar
Scene <|-- PickCard

%% Characters
Game o-- Character : contains
CharacterManager o-- Character : manages
Character *-- Animation : uses
Character *-- attributesCharacter : has

%% Battle
BattleScene ..> BattleState : uses
BattleScene *-- QueuedAction : contains

%% Cards / Actions
Card *-- IAction : contains
IAction <|.. DamageAction
IAction <|.. HealAction

%% Resource / Deck
DeckManager o-- Card : manages
Card ..> Resource : uses
Animation ..> Resource : uses
Character ..> Resource : uses
Card ..> Params : uses