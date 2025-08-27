# UML Class Diagram - Game Project

```mermaid
classDiagram
    %% ========================================
    %% CORE GAME SYSTEM
    %% ========================================
    class Game {
        -Character* player
        -Character* enemy
        -vector~string~ desk1
        -vector~string~ desk2
        -unique_ptr~Scene~ currentScene
        -unique_ptr~Scene~ m_nextScene
        -std::any m_sceneData
        -bool m_isChangingScene
        -bool shouldClose
        +~Game()
        +run() void
        +switchScene(unique_ptr~Scene~) void
        +closeGame() void
        +requestSceneChange(unique_ptr~Scene~, std::any) void
        +getSceneData() const std::any&
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
        -vector~QueuedAction~ actionQueue_2
        +int cardPlay
        +float timeerrr
        +vector~int~ id1, id2
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
        -map~string, unique_ptr~Character~~ m_characters
        -CharacterManager()
        -CharacterManager(const CharacterManager&)
        -CharacterManager operator=(const CharacterManager&)
        +getInstance() CharacterManager&
        +loadChar() void
        +GetCharacter(string&) Character*
        +PrintAll() void
    }

    class Character {
        -bool m_isMoving
        -Vector2 m_startPos
        -Vector2 m_endPos
        -float m_moveTimer
        -float m_moveDuration
        +string name
        +attributesCharacter attributes
        +Vector2 point
        +Vector2 rootPoint
        +bool isFlipped
        +string currentAnimation
        +map~string, unique_ptr~Animation~~ animations
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

    class attributesCharacter {
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
        +vector~unique_ptr~IAction~~ actions
        +Card()
        +Card(string, string)
        +AddAction(unique_ptr~IAction~) void
        +Draw(Vector2&, float) void
        +setDataFromParams(string&) void
        +printInfo() void
    }

    class IAction {
        <<interface>>
        +~IAction()
        +Execute(Character&, Character&) void
        +GetAnimationKey() string&
        +GetValue() int
        +clone() unique_ptr~IAction~
        +printInfo() void
    }

    class DamageAction {
        +int amount
        +string key
        +DamageAction()
        +~DamageAction()
        +DamageAction(string, int)
        +Execute(Character&, Character&) void
        +GetAnimationKey() string&
        +GetValue() int
        +clone() unique_ptr~IAction~
        +printInfo() void
    }

    class HealAction {
        -int amount
        -string key
        +HealAction()
        +~HealAction()
        +HealAction(string, int)
        +Execute(Character&, Character&) void
        +GetAnimationKey() string&
        +GetValue() int
        +clone() unique_ptr~IAction~
        +printInfo() void
    }

    %% ========================================
    %% RESOURCE MANAGEMENT
    %% ========================================
    class Resource {
        -map~string, Texture2D~ textures
        -vector~string~ idTexture2D
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
        +getTexture2D(string&) Texture2D&
        +getTexture2D(Card&) Texture2D&
        +getTexture2D(Animation&) Texture2D&
        +Print() void
        +isValidTexture(Texture2D&) bool
    }

    class DeckManager {
        -map~string, unique_ptr~Card~~ allCards
        -DeckManager()
        -DeckManager(const Resource&)
        -DeckManager operator=(const Resource&)
        +getInstance() DeckManager&
        +InitializeDeck() void
        +GetCardByID(string&) Card*
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
        +getInt(string&, int) int
        +getString(string&, string&) string
        +parseParams(string&) void
        +parseParamsFromFile(string&) bool
    }

    %% ========================================
    %% RELATIONSHIPS - CORE SYSTEM
    %% ========================================
    Game ||--o{ Scene : "manages"
    Scene <|-- Credits : "implements"
    Scene <|-- MainMenuScene : "implements"
    Scene <|-- BattleScene : "implements"
    Scene <|-- ChoseChar : "implements"
    Scene <|-- PickCard : "implements"

    %% ========================================
    %% RELATIONSHIPS - CHARACTER SYSTEM
    %% ========================================
    Game ||--o{ Character : "contains"
    CharacterManager ||--o{ Character : "manages"
    Character ||--|| attributesCharacter : "has"
    Character ||--o{ Animation : "uses"

    %% ========================================
    %% RELATIONSHIPS - CARD SYSTEM
    %% ========================================
    Card ||--o{ IAction : "contains"
    IAction <|-- DamageAction : "implements"
    IAction <|-- HealAction : "implements"

    %% ========================================
    %% RELATIONSHIPS - RESOURCE MANAGEMENT
    %% ========================================
    DeckManager ||--o{ Card : "manages"

    %% ========================================
    %% RELATIONSHIPS - RESOURCE USAGE
    %% ========================================
    Card ||--|| Resource : "uses"
    Animation ||--|| Resource : "uses"
    Character ||--|| Resource : "uses"
    Card ||--|| Params : "uses"

    %% ========================================
    %% NOTES
    %% ========================================
    note for Game "🎮 Main Game Controller\n- Manages scene transitions\n- Controls game state\n- Handles player/enemy"
    note for Scene "📺 Abstract Base Class\n- Template for all scenes\n- Lifecycle management"
    note for Character "👤 Game Character\n- Has animations\n- Contains attributes\n- Movement system"
    note for Card "🃏 Card-based Gameplay\n- Contains multiple actions\n- Strategy pattern"
    note for IAction "⚔️ Strategy Pattern\n- Different card effects\n- Polymorphic behavior"
    note for Resource "📦 Singleton Pattern\n- Global texture manager\n- Memory optimization"
    note for DeckManager "🎴 Singleton Pattern\n- Card collection manager\n- Random card selection"
    note for CharacterManager "👥 Character Manager\n- Singleton pattern\n- Character lifecycle"
```

## 🎮 Mô tả chi tiết hệ thống Game

### **1. Core Game System** 🎯
- **Game**: Class chính điều khiển toàn bộ game, quản lý scene transitions và game state
- **Scene**: Abstract base class định nghĩa lifecycle cho tất cả các scene
- **Scene Implementations**: Credits, MainMenuScene, BattleScene, ChoseChar, PickCard

### **2. Character System** 👤
- **CharacterManager**: Singleton pattern quản lý tất cả characters trong game
- **Character**: Đại diện cho nhân vật với hệ thống animation và movement
- **attributesCharacter**: Struct chứa các thuộc tính (HP, attack, defense, mana)
- **Animation**: Quản lý sprite-based animations với frame timing

### **3. Card System** 🃏
- **Card**: Lá bài chứa nhiều actions có thể thực thi
- **IAction**: Interface cho Strategy pattern, cho phép các hành động khác nhau
- **DamageAction/HealAction**: Các implementation cụ thể của IAction

### **4. Resource Management** 📦
- **Resource**: Singleton pattern quản lý tất cả textures và memory
- **DeckManager**: Singleton pattern quản lý bộ bài và card collection

### **5. Utilities** ⚙️
- **Params**: Container cho parameters với parsing capabilities từ file

## 🏗️ Design Patterns được sử dụng:

| Pattern | Classes | Mục đích |
|---------|---------|----------|
| **Singleton** | Resource, DeckManager, CharacterManager | Quản lý global state và resources |
| **Strategy** | IAction, DamageAction, HealAction | Polymorphic card effects |
| **State** | Scene transitions | Quản lý game states |
| **Observer** | Game state management | Event handling |

## 🔄 Luồng hoạt động chính:

1. **Game Loop**: Game class quản lý main loop và scene transitions
2. **Scene Management**: Mỗi scene có lifecycle riêng (onEnter, update, draw, onExit)
3. **Character Management**: CharacterManager quản lý tất cả characters
4. **Card System**: Cards chứa actions được thực thi thông qua Strategy pattern
5. **Resource Management**: Singleton patterns đảm bảo efficient resource usage

## 📁 Cấu trúc thư mục tương ứng:

```
Source/
├── core/           # Game engine core (Resource, Animation)
├── scenes/         # Scene implementations  
├── game_objects/   # Characters, actions, managers
│   ├── character/  # Character, CharacterManager
│   └── actions/    # IAction, DamageAction, HealAction
├── cards/          # Card system, DeckManager
└── utils/          # Utilities, params
```

## 🎯 Điểm nổi bật của kiến trúc:

1. **Modular Design**: Hệ thống được chia thành các module rõ ràng
2. **Singleton Pattern**: Đảm bảo single instance cho global managers
3. **Strategy Pattern**: Cho phép dễ dàng thêm card effects mới
4. **Resource Management**: Efficient memory usage và texture management
5. **Scene System**: Clean separation of game states
6. **Manual Action Creation**: Actions được tạo thủ công trong Card class
