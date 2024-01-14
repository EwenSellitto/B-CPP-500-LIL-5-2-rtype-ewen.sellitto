# R-Type/GameWorld Technical Documentation

# EnemyMakers.hpp
```cpp
#pragma once

#include <SFML/System.hpp>
#include <functional>
#include <map>
#include <vector>

namespace EnemyMakers
{
    std::size_t basicEnemyMaker(float y, bool isAttacking, std::vector<std::pair<std::size_t, sf::Vector2f>>);
    std::size_t mediumEnemyMaker(float y, bool isAttacking, std::vector<std::pair<std::size_t, sf::Vector2f>>);
    std::size_t strongEnemyMaker(float y, bool isAttacking, std::vector<std::pair<std::size_t, sf::Vector2f>>);
    std::size_t ObstacleMaker(float y, bool isAttacking, std::vector<std::pair<std::size_t, sf::Vector2f>>);
} // namespace EnemyMakers

extern std::map<std::size_t, std::function<size_t(float, bool, std::vector<std::pair<size_t, sf::Vector2f>>)>>
    functionMap;
```

### **`EnemyMakers` Namespace:**

1. **Purpose:**
    - Provides functions for creating different types of enemies and obstacles.
    - Defines a map (**`functionMap`**) to associate unique identifiers with corresponding enemy-making functions.
2. **Included Headers:**
    - **`<SFML/System.hpp>`**
    - **`<functional>`**
    - **`<map>`**
    - **`<vector>`**
3. **Namespace:**
    - **`EnemyMakers`**
4. **Functions:**
    - **`basicEnemyMaker`**:
        - Parameters:
            - **`y`** (type: **`float`**): Y-coordinate for the enemy.
            - **`isAttacking`** (type: **`bool`**): Indicates whether the enemy is in attacking mode.
            - **`positions`** (type: **`std::vector<std::pair<std::size_t, sf::Vector2f>>`**): Vector of positions, each represented as a pair of identifier and 2D vector.
        - Returns: **`std::size_t`** identifier for the created enemy.
    - **`mediumEnemyMaker`**:
        - Parameters and return type similar to **`basicEnemyMaker`**.
    - **`strongEnemyMaker`**:
        - Parameters and return type similar to **`basicEnemyMaker`**.
    - **`ObstacleMaker`**:
        - Parameters and return type similar to **`basicEnemyMaker`**.
5. **External Declarations:**
    - **`extern std::map<std::size_t, std::function<size_t(float, bool, std::vector<std::pair<size_t, sf::Vector2f>>)>> functionMap;`**
        - External declaration of a map associating identifiers with enemy-making functions.


# Entities.hpp


### **`Entities` Namespace:**

```cpp
#include "ECS/World.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Cursor.component.hpp"
#include "Engine/Components/LayeredAnimation.component.hpp"
#include "Engine/Components/LayeredRenderable.component.hpp"
#include "Engine/Components/Menu.component.hpp"
#include "Engine/Components/Music.component.hpp"
#include "Engine/Components/Options.component.hpp"
#include "Engine/Components/Parallax.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Score.component.hpp"
#include "Engine/Components/Speed.component.hpp"
#include "Engine/Components/Text.component.hpp"
#include "Engine/Components/TextInput.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
#include "Engine/Systems/Inputs.system.hpp"
#include "Engine/Systems/Options.system.hpp"
#include "Engine/Systems/Sound.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "R-Type/Components/EnemyQueue.component.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/Components/WeaponType.component.hpp"
#include "Waves.hpp"

namespace Entities
{
    inline void createViewEntity(ECS::World *world)
    {
        ECS::id_t ship_id = world->createEntity(new Engine::Components::ViewComponent());

        auto &entity = world->getMutEntity(ship_id);
        for (auto &it : entity.getComponents())
            it.second->setHasChanged(false);
    }

    inline void createPlayerEntities(ECS::World *world, int playerNb)
    {
        using namespace Engine::Components;
        std::vector<std::pair<int, int>> playerPos = {{100, 300}, {100, 360}, {100, 420}, {100, 480}};

        world->createEntity(
            new PlayerComponent(playerNb), new PositionComponent(playerPos[playerNb].first, playerPos[playerNb].second),
            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 2, 90),
            new LayeredRenderableComponent(
                1, new RenderableComponent("./assets/MainShip/MainShip-Engines-BaseEngine-Powering.png", 0, 0, 1, 90),
                new RenderableComponent("./assets/MainShip/MainShip-Weapons-BigSpaceGun-Croped.png", 0, 0, 1, 90,
                                        {1, 1}, false, false),
                new RenderableComponent("./assets/MainShip/MainShip-Weapons-Rockets-Croped.png", 0, 0, 1, 90),
                new RenderableComponent("./assets/MainShip/MainShip-Engines-BaseEngine.png", 0, 0, 1, 90)),
            new LayeredAnimationComponent(new AnimationComponent(0, 0, 48, 48, 48, 48, 100, 4)),
            new CollisionComponent(9, 11, 30, 26), new SpeedComponent(150),
            new Rtype::Components::WeaponTypeComponent(Rtype::Components::WeaponType::BASIC));
    }

    inline void createInputsEntitiesForJoin(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font.ttf")) {
            return;
        }
        world->createEntity(
            new PositionComponent(400, 200), new TextComponent("IP", font, 30, {310, 180}, false, true),
            new OptionsComponent(), new TextInputComponent("IP", []() {}),
            new RenderableComponent("./assets/menu/button_long/long_focus.png", 0, 0, 3, 0, {2, 2}, true));
        world->createEntity(
            new PositionComponent(400, 300), new TextComponent("PORT", font, 30, {310, 280}, false, true),
            new OptionsComponent(), new TextInputComponent("PORT", []() {}),
            new RenderableComponent("./assets/menu/button_long/long_focus.png", 0, 0, 3, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(400, 410),
                            new TextComponent("Send", font, 40, {400, 385}, true, true), new OptionsComponent(),
                            new ButtonComponent("send",
                                                [world]() {
                                                    Engine::System::InputsSystem inputsSystem =
                                                        Engine::System::InputsSystem(*world);
                                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                                    inputsSystem.handleSend({"PORT", "IP"});
                                                    uiSystem.handleGoWaitingClient();
                                                }),
                            new RenderableComponent("./assets/menu/button_long/long_on.png", 0, 0, 3, 0, {2, 2}, true));
        world->createEntity(
            new PositionComponent(40, 100), new MenuComponent(),
            new ButtonComponent("Pause Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleGoMenu();
                                    NETWORK.resetServer();
                                }),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(30, 100), new MenuComponent(),
                            new RenderableComponent("./assets/menu/icons/close_icon.png", 0, 0, 2, 0, {2, 2}, true));
    }

    inline void createWaitingHostEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font.ttf")) {
            return;
        }
        Engine::EngineClass &engine = Engine::EngineClass::getEngine();
        std::string          str    = "Nombre de joueurs : " + std::to_string(engine.getPlayersAmount()) + "/4";
        world->createEntity(new TextComponent(str, font, 30, {310, 180}, false, true));
        std::string strServer = "Server IP : " + engine.network().getIP().toString();
        world->createEntity(new TextComponent(strServer, font, 30, {310, 280}, false, true));
        std::string strPort = "Port : " + std::to_string(engine.network().getPort());
        world->createEntity(new TextComponent(strPort, font, 30, {310, 380}, false, true));
        world->createEntity(
            new PositionComponent(40, 100), new MenuComponent(),
            new ButtonComponent("Pause Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleGoJoin();
                                }),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(30, 100), new MenuComponent(),
                            new RenderableComponent("./assets/menu/icons/close_icon.png", 0, 0, 2, 0, {2, 2}, true));
        world->createEntity(
            new PositionComponent(400, 520), new TextComponent("Start Game", font, 40, {400, 500}, true),
            new MenuComponent(), new ButtonComponent("Start Game", []() { NETWORK.setIsReadyToStart(true); }),
            new RenderableComponent("./assets/menu/button_long/long_off.png", 0, 0, 1, 0, {2, 2}, true));
    }

    inline void createWaitingClientEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font.ttf")) {
            return;
        }
        Engine::EngineClass &engine = Engine::EngineClass::getEngine();
        std::string strServer = "Server IP : " + engine.network().getIP().toString();
        world->createEntity(new TextComponent(strServer, font, 30, {310, 280}, false, true));
        std::string strPort = "Port : " + std::to_string(engine.network().getPort());
        world->createEntity(new TextComponent(strPort, font, 30, {310, 380}, false, true));
        world->createEntity(
            new PositionComponent(40, 100), new MenuComponent(),
            new ButtonComponent("Pause Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleGoJoin();
                                }),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(30, 100), new MenuComponent(),
                            new RenderableComponent("./assets/menu/icons/close_icon.png", 0, 0, 2, 0, {2, 2}, true));
        world->createEntity(new TextComponent("Waiting for the host ...", font, 40, {400, 500}, true));
    }

    inline void createInputsEntitiesForCreate(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font.ttf")) {
            return;
        }
        world->createEntity(
            new PositionComponent(400, 200), new TextComponent("PORT", font, 30, {310, 180}, false, true),
            new OptionsComponent(), new TextInputComponent("PORT", []() {}),
            new RenderableComponent("./assets/menu/button_long/long_focus.png", 0, 0, 3, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(400, 410),
                            new TextComponent("Send", font, 40, {400, 385}, true, true), new OptionsComponent(),
                            new ButtonComponent("send",
                                                [world]() {
                                                    Engine::System::InputsSystem inputsSystem =
                                                        Engine::System::InputsSystem(*world);
                                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                                    inputsSystem.handleSend({"PORT"});
                                                    uiSystem.handleGoWaitingHost();
                                                }),
                            new RenderableComponent("./assets/menu/button_long/long_on.png", 0, 0, 3, 0, {2, 2}, true));
        world->createEntity(
            new PositionComponent(40, 100), new MenuComponent(),
            new ButtonComponent("Pause Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleGoMenu();
                                    NETWORK.resetServer();
                                }),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(30, 100), new MenuComponent(),
                            new RenderableComponent("./assets/menu/icons/close_icon.png", 0, 0, 2, 0, {2, 2}, true));
    }
    inline void createGameOverEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font_big.ttf")) {
            return;
        }
        world->createEntity(new TextComponent("Game over", font, 80, {400, 50}, sf::Color::White, true));
        world->createEntity(new PositionComponent(400, 325),
                            new TextComponent("Restart", font, 40, {400, 300}, true, true),
                            new ButtonComponent("Restart",
                                                [world]() {
                                                    NETWORK.resetServer();
                                                    NETWORK.startServer(5555, true);
                                                    // sleep 200 ms
                                                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                                                    NETWORK.setIsReadyToStart(true);
                                                }),
                            new RenderableComponent("./assets/menu/button_long/long_on.png", 0, 0, 3, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(400, 410),
                            new TextComponent("Menu", font, 40, {400, 385}, true, true),
                            new ButtonComponent("Menu",
                                                [world]() {
                                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                                    uiSystem.handleGoMenu();
                                                    NETWORK.resetServer();
                                                }),
                            new RenderableComponent("./assets/menu/button_long/long_on.png", 0, 0, 3, 0, {2, 2}, true));
    }

    inline void createScoreEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font.ttf")) {
            return;
        }
        world->createEntity(new TextComponent("Score : 0", font, 30, {650, 10}, sf::Color::White),
                            new ScoreComponent(0));
    }

    inline void createOptionsEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font_big.ttf")) {
            return;
        }
        world->createEntity(new TextComponent("Options", font, 80, {550, 50}, sf::Color::White, false, false),
                            new OptionsComponent());
        world->createEntity(new RenderableComponent("./assets/menu/panel/options.png", 0, 0, 1, 0, {2, 2}, true, false),
                            new PositionComponent(450, 300), new OptionsComponent());
        world->createEntity(
            new PositionComponent(360, 300), new TextComponent("vsync", font, 40, {250, 300}, false, false),
            new OptionsComponent(),
            new CheckBoxComponent(
                "vsync", []() { Engine::EngineClass::getEngine().window.setVerticalSyncEnabled(true); },
                []() { Engine::EngineClass::getEngine().window.setVerticalSyncEnabled(false); }, false),
            new RenderableComponent("./assets/menu/button_check/check_off.png", 0, 0, 3, 0, {2, 2}, false, false));
        world->createEntity(
            new PositionComponent(650, 300), new TextComponent("FullScreen", font, 40, {520, 300}, false, false),
            new OptionsComponent(),
            new CheckBoxComponent(
                "vsync", []() { Engine::EngineClass::getEngine().toggleFullscreen(); },
                []() { Engine::EngineClass::getEngine().toggleFullscreen(); }, false),
            new RenderableComponent("./assets/menu/button_check/check_off.png", 0, 0, 3, 0, {2, 2}, false, false));
        world->createEntity(
            new PositionComponent(250, 450), new TextComponent("musique", font, 40, {250, 400}, false, false),
            new RenderableComponent("./assets/menu/range/barre_pleine.png", 0, 0, 3, 0, {2, 2}, false, false),
            new OptionsComponent());
        world->createEntity(
            new PositionComponent(370, 465), new CursorComponent([world]() {
                Engine::System::Sound SoundSystem = Engine::System::Sound(*world);
                SoundSystem.SetVolumeMusic();
            }),
            new OptionsComponent(),
            new RenderableComponent("./assets/menu/range/grabber_on.png", 0, 0, 4, 0, {2, 2}, true, false));
        world->createEntity(
            new PositionComponent(520, 450), new TextComponent("SFX", font, 40, {520, 400}, false, false),
            new OptionsComponent(),
            new RenderableComponent("./assets/menu/range/barre_pleine.png", 0, 0, 3, 0, {2, 2}, false, false));
        world->createEntity(new PositionComponent(40, 100), new OptionsComponent(),
                            new ButtonComponent("Pause Game",
                                                [world]() {
                                                    Engine::System::OptionsSystem OptionsComponent =
                                                        Engine::System::OptionsSystem(*world);
                                                    OptionsComponent.closeOptions();
                                                }),
                            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0,
                                                    {2, 2}, true, false));
        world->createEntity(
            new PositionComponent(30, 100), new OptionsComponent(),
            new RenderableComponent("./assets/menu/icons/close_icon.png", 0, 0, 2, 0, {2, 2}, true, false));
        world->createEntity(new MusicComponent("./assets/Music/MusicMenu.ogg"));
    }

    inline void createButtonEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font_big.ttf")) {
            return;
        }
        world->createEntity(new TextComponent("R-Type", font, 110, {400, 50}, true), new MenuComponent());

        world->createEntity(
            new PositionComponent(400, 220), new TextComponent("Start", font, 40, {400, 200}, true),
            new MenuComponent(),
            new ButtonComponent("Start Game",
                                [world]() {
                                    NETWORK.startServer(5555, true);
                                    // sleep 200 ms
                                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                                    NETWORK.setIsReadyToStart(true);
                                }),
            new RenderableComponent("./assets/menu/button_long/long_off.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(
            new ButtonComponent("Start Room",
                                []() {
                                    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
                                    engine.switchWorld("createRoom");
                                }),
            new PositionComponent(400, 320), new TextComponent("Start Room", font, 40, {400, 300}, true),
            new MenuComponent(),
            new RenderableComponent("././assets/menu/button_long/long_off.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(
            new ButtonComponent("Join Room",
                                []() {
                                    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
                                    engine.switchWorld("joinRoom");
                                }),
            new PositionComponent(400, 420), new TextComponent("Join Room", font, 40, {400, 400}, true),
            new MenuComponent(),
            new RenderableComponent("././assets/menu/button_long/long_off.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(
            new PositionComponent(400, 520), new TextComponent("Quit", font, 40, {400, 500}, true), new MenuComponent(),
            new ButtonComponent("Quit",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleQuitGame();
                                }),
            new RenderableComponent("./assets/menu/button_long/long_off.png", 0, 0, 1, 0, {2, 2}, true));

        world->createEntity(
            new PositionComponent(40, 100), new MenuComponent(),
            new ButtonComponent("Pause Game",
                                [world]() {
                                    Engine::System::OptionsSystem OptionsComponent =
                                        Engine::System::OptionsSystem(*world);
                                    OptionsComponent.openOptions();
                                }),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(30, 100), new MenuComponent(),
                            new RenderableComponent("./assets/menu/icons/settings_icon.png", 0, 0, 2, 0, {2, 2}, true));
    }

    inline void createBackground(ECS::World *world, const std::string &texturePath, ParallaxLayer layer, float speed,
                                 bool first, int priority)
    {

        using namespace Engine::Components;
        sf::Vector2f windowSize = {0, 0};

        world->each<ViewComponent>(
            [&windowSize]([[maybe_unused]] ECS::Entity *entity, ECS::ComponentHandle<ViewComponent> viewComp) {
                windowSize = viewComp->view.getSize();
            });

        auto  renderable = new RenderableComponent(texturePath, {0, 0}, priority);
        float scaleRatio = windowSize.y / renderable->texture.getSize().y;

        renderable->scale           = {scaleRatio, scaleRatio};
        sf::Vector2<float> trueSize = {static_cast<float>(renderable->size.x * scaleRatio),
                                       static_cast<float>(renderable->size.y * scaleRatio)};
        if (first) {
            renderable->position = {0, 0};
            ECS::id_t ship_id =
                world->createEntity(new PositionComponent(0, 0), renderable, new ParallaxComponent(layer, speed));
            auto &entity = world->getMutEntity(ship_id);
            for (auto &it : entity.getComponents())
                it.second->setHasChanged(false);
        } else {
            renderable->position = {trueSize.x, 0};
            ECS::id_t ship_id    = world->createEntity(new PositionComponent(trueSize.x, 0), renderable,
                                                       new ParallaxComponent(layer, speed));
            auto     &entity     = world->getMutEntity(ship_id);
            for (auto &it : entity.getComponents())
                it.second->setHasChanged(false);
        }
    }

    inline void createChangeSceneButton(ECS::World *world, [[maybe_unused]] const std::string &texturePath,
                                        [[maybe_unused]] const std::string  &sceneName,
                                        [[maybe_unused]] const sf::Vector2f &position,
                                        [[maybe_unused]] const sf::Vector2f &scale, [[maybe_unused]] int priority)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font_big.ttf")) {
            return;
        }
        world->createEntity(
            new PositionComponent(40, 100), new MenuComponent(),
            new ButtonComponent("Pause Game",
                                [world]() {
                                    Engine::System::OptionsSystem OptionsComponent =
                                        Engine::System::OptionsSystem(*world);
                                    OptionsComponent.openOptions();
                                }),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(30, 100), new MenuComponent(),
                            new RenderableComponent("./assets/menu/icons/settings_icon.png", 0, 0, 2, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(position.x, position.y),
                            new TextComponent(sceneName, font, 40, {position.x, position.y - 20}, true, false),
                            new OptionsComponent(),
                            new ButtonComponent(sceneName,
                                                [world]() {
                                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                                    uiSystem.handleGoMenu();
                                                    NETWORK.resetServer();
                                                }),
                            new RenderableComponent(texturePath, 0, 0, 3, 0, {2, 2}, true, false));
    }

    inline void createParallax(ECS::World *world)
    {
        createBackground(world, "./assets/Environnement/Starrybackground-Layer01-Void.png",
                         ParallaxLayer::FarBackground, 1, true, -5);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer01-Void.png",
                         ParallaxLayer::FarBackground, 1, false, -5);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer02-Stars.png",
                         ParallaxLayer::MidBackground, 2, true, -4);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer02-Stars.png",
                         ParallaxLayer::MidBackground, 2, false, -4);
        createBackground(world, "./assets/Environnement/Starrybackground-LayerX-BigStar2.png",
                         ParallaxLayer::NearBackground, 4, true, -3);
        createBackground(world, "./assets/Environnement/Starrybackground-LayerX-BigStar2.png",
                         ParallaxLayer::NearBackground, 4, false, -3);
    }

    inline void createEnemyQueue(ECS::World *world)
    {
        using namespace Engine::Components;

        auto WeakUpAndDown    = enemyPatternMovements.find("WeakUpAndDown");
        auto WeakLeft         = enemyPatternMovements.find("WeakLeft");
        auto WeakDiagBotToTop = enemyPatternMovements.find("WeakDiagBotToTop");
        auto WeakDiagTopToBot = enemyPatternMovements.find("WeakDiagTopToBot");

        auto MediumUpAndDown = enemyPatternMovements.find("MediumUpAndDown");

        world->createEntity(new EnemyQueueComponent({

            // twin snake 1
            std::make_pair(false, std::make_pair(std::make_tuple(160, 200, true, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(170, 210, false, WeakUpAndDown->second), 0)),

            ect...

            std::make_pair(false, std::make_pair(std::make_tuple(3250, 350, true,MediumUpAndDown->second), 2)),
        }));
    }

    inline void createWorldMoveProgress(ECS::World *world)
    {
        using namespace Engine::Components;

        auto   now         = std::chrono::high_resolution_clock::now();
        auto   epoch       = now.time_since_epoch();
        size_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

        world->createEntity(new WorldMoveProgressComponent(currentTime, 0, 50));
    }
} // namespace Entities
```

1. **Purpose:**
    - Encapsulates functions for creating entities in the game world.
    - Covers various entities related to player, inputs, game state, UI, and more.
2. **Functions:**
    - **`createViewEntity`**:
        - Creates a view entity with a **`ViewComponent`**.
    - **`createPlayerEntities`**:
        - Creates player entities with various components like **`PlayerComponent`**, **`PositionComponent`**, **`RenderableComponent`**, etc.
    - **`createInputsEntitiesForJoin`**:
        - Creates UI input-related entities for joining a game.
    - **`createWaitingHostEntities`**:
        - Creates UI entities for the waiting host screen.
    - **`createWaitingClientEntities`**:
        - Creates UI entities for the waiting client screen.
    - **`createInputsEntitiesForCreate`**:
        - Creates UI input-related entities for creating a game.
    - **`createGameOverEntities`**:
        - Creates UI entities for the game over screen.
    - **`createScoreEntities`**:
        - Creates a score entity with **`ScoreComponent`**.
    - **`createOptionsEntities`**:
        - Creates UI entities for the options screen.
    - **`createButtonEntities`**:
        - Creates UI button entities for the main menu.
    - **`createBackground`**:
        - Creates parallax background entities based on the provided parameters.
    - **`createChangeSceneButton`**:
        - Creates a button entity for changing the scene.
    - **`createParallax`**:
         - Creates a set of parallax backgrounds to simulate depth in the game world.
    - **`createEnemyQueue`**:
        - Creates an enemy queue for defining enemy patterns.
    - **`createWorldMoveProgress`**:
        - Creates an entity to track the progress of the world movement.


# GameWorld.cpp
```cpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "Entities.hpp"
#include "Subscribers.hpp"
#include "Systems.hpp"

namespace GameWorld
{
    inline ECS::World *createGameWorld()
    {
        auto world = new ECS::World();

        // Setup view and create entities
        Entities::createViewEntity(world);
        Entities::createParallax(world);
        Entities::createPlayerEntities(world);
        Entities::createEnemyQueue(world);
        Entities::createWorldMoveProgress(world);

        // Add systems
        Systems::addPhysics(world);
        Systems::addPlayerMovement(world);
        Systems::addEnemySystem(world);
        Systems::addParallaxSystem(world);
        Systems::addBulletSystem(world);
        Systems::addWorldMoveSystem(world);
        Systems::addAnimationSystem(world);

        // Subscribe to events
        Subscribers::subscribeToEvents(world);

        return world;
    }

    inline ECS::World *createMenuWorld()
    {
        auto world = new ECS::World();

        Entities::createViewEntity(world);
        Entities::createButtonEntities(world);

        Systems::addUISystem(world);

        return world;
    }
} // namespace GameWorld
```
### **`createGameWorld`**

- Creates the game world by initializing the ECS world instance.
- Sets up the view and creates various entities including the view, parallax layers, player entities, enemy queues, and world progression.
- Adds different systems related to physics, player movement, enemies, parallax effects, bullets, world movement, and animation to the world.
- Subscribes to events to handle interactions and events within the game.

### **`createMenuWorld`**

- Generates a menu world by initializing a separate ECS world instance.
- Creates entities for the view and buttons meant for the game menu.
- Adds a UI system to handle user interface-related logic within the menu.

The functions encapsulate the process of creating distinct game worlds, each tailored to different parts of the game—either the actual gameplay or the menu interface—by setting up entities, systems, and event subscriptions as needed within the ECS framework.

# Subscribers.hpp
```cpp
#pragma once

#include "ECS/World.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "R-Type/Events/EnnemyDeath.event.hpp"
#include "R-Type/Subscribers/Collision.subscriber.hpp"
#include "R-Type/Subscribers/EnnemyDeath.subscriber.hpp"
#include "R-Type/Subscribers/Keyboard.subscriber.hpp"
#include "R-Type/Subscribers/PlayerMove.subscriber.hpp"
#include "R-Type/Subscribers/ShootPlayer.subscriber.hpp"

namespace Subscribers
{
    inline void subscribeToEvents(ECS::World *world)
    {
        auto *subMovePressed  = new Rtype::Subscriber::PlayerMovePressedSubscriber();
        auto *subMoveReleased = new Rtype::Subscriber::PlayerMoveReleasedSubscriber();
        auto *subCollision    = new Rtype::Subscriber::CollisionEventSubscriber();
        auto *subShootPlayer  = new Rtype::Subscriber::ShootPlayerReleasedSubscriber();
        auto *subShootPlayer2 = new Rtype::Subscriber::ShootPlayerPressedSubscriber();
        auto *subEnnemyDeath  = new Rtype::Subscriber::EnnemyDeathSubscriber();
        auto *subChangeWeapon = new Rtype::Subscriber::ChangeWeapon();

        world->subscribe<KeyPressedEvent>(subMovePressed);
        world->subscribe<KeyReleasedEvent>(subMoveReleased);
        world->subscribe<CollisionEvent>(subCollision);
        world->subscribe<KeyReleasedEvent>(subShootPlayer);
        world->subscribe<KeyPressedEvent>(subShootPlayer2);
        world->subscribe<KeyPressedEvent>(subChangeWeapon);
        world->subscribe<Rtype::Events::EnnemyDeath>(subEnnemyDeath);
    }

    inline void subscribeToEventsInputs(ECS::World *world)
    {
        auto *keyboardPressed  = new Rtype::Subscriber::KeyboardPressedSubscriber();
        auto *keyboardReleased = new Rtype::Subscriber::KeyboardReleasedSubscriber();

        world->subscribe<KeyPressedEvent>(keyboardPressed);
        world->subscribe<KeyReleasedEvent>(keyboardReleased);
    }
} // namespace Subscribers
```

### **`Subscribers` Namespace:**

1. **Purpose:**
    - The **`Subscribers`** namespace provides functions to subscribe to various events in the game using ECS (Entity-Component-System) architecture.
2. **Functions:**
    - **`subscribeToEvents`**:
            - Subscribes various subscriber objects to specific events such as player movement, collisions, shooting, weapon change, and enemy death.
    - **`subscribeToEventsInputs`**:
            - Subscribes keyboard-related subscriber objects to key press and release events.
3. **Subscriber Objects:**
    - **`PlayerMovePressedSubscriber`**: Handles player movement when a key is pressed.
    - **`PlayerMoveReleasedSubscriber`**: Handles player movement when a key is released.
    - **`CollisionEventSubscriber`**: Handles collision events.
    - **`ShootPlayerReleasedSubscriber`**: Handles shooting when a key is released.
    - **`ShootPlayerPressedSubscriber`**: Handles shooting when a key is pressed.
    - **`EnnemyDeathSubscriber`**: Handles enemy death events.
    - **`ChangeWeaponSubscriber`**: Handles events related to changing the player's weapon.
    - **`KeyboardPressedSubscriber`**: Handles keyboard events when a key is pressed.
    - **`KeyboardReleasedSubscriber`**: Handles keyboard events when a key is released.



# Systems.hpp
```cpp
#pragma once

#include "ECS/World.hpp"
#include "Engine/Systems/Animation.system.hpp"
#include "Engine/Systems/Parallax.system.hpp"
#include "Engine/Systems/Physics.system.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "Engine/Systems/Score.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "Engine/Systems/WorldMove.system.hpp"
#include "R-Type/Systems/Booster.system.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "R-Type/Systems/DeathAnimation.system.hpp"
#include "R-Type/Systems/Enemy.system.hpp"
#include "R-Type/Systems/Health.system.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"

namespace Systems
{
    inline void addRenderer(ECS::World *world)
    {
        world->addSystem<Engine::System::Renderer>("Renderer");
    }

    inline void addPhysics(ECS::World *world)
    {
        world->addSystem<Engine::System::Physics>("Physics");
    }

    inline void addPlayerMovement(ECS::World *world)
    {
        world->addSystem<Engine::System::MovePlayer>("MovePlayer");
    }

    inline void addEnemySystem(ECS::World *world)
    {
        world->addSystem<Engine::System::EnemySystem>("EnemySystem");
    }

    inline void addParallaxSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::ParallaxSystem>("ParallaxSystem");
    }

    inline void addUISystem(ECS::World *world)
    {
        world->addSystem<Engine::System::UI>("UISystem");
    }

    inline void addScoreSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::ScoreSystem>("ScoreSystem");
    }

    inline void addInputsSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::InputsSystem>("InputsSystem");
    }

    inline void addBulletSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::Bullets>("BulletsSystem");
    }

    inline void addWorldMoveSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::WorldMoveSystem>("WorldMoveSystem");
    }

    inline void addAnimationSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::AnimationSystem>("AnimationSystem");
    }

    inline void addDeathAnimationSystem(ECS::World *world)
    {
        world->addSystem<Engine::System::DeathAnimationSystem>("DeathAnimationSystem");
    }

    inline void addHealthSystem(ECS::World *world)
    {
        world->addSystem<Rtype::Systems::HealthSystem>("HealthSystem");
    }

    inline void addBoosterSystem(ECS::World *world)
    {
        world->addSystem<Rtype::System::BoosterSystem>("BoosterSystem");
    }
} // namespace Systems
```

### **`Systems` Namespace:**

1. **Purpose:**
    - The **`Systems`** namespace provides functions to add various systems to an ECS (Entity-Component-System) world. Each system is responsible for specific aspects of the game logic, such as rendering, physics, player movement, enemy behavior, etc.
2. **Functions:**
    - **`addRenderer`**:
        - Adds the **`Renderer`** system to the ECS world, responsible for rendering entities.
    - **`addPhysics`**:
        - Adds the **`Physics`** system to the ECS world, responsible for handling physics-related aspects.
    - **`addPlayerMovement`**:
        - Adds the **`MovePlayer`** system to the ECS world, responsible for handling player movement.
    - **`addEnemySystem`**:
        - Adds the **`EnemySystem`** to the ECS world, responsible for managing enemy entities.
    - **`addParallaxSystem`**:
        - Adds the **`ParallaxSystem`** to the ECS world, responsible for handling parallax scrolling.
    - **`addUISystem`**:
        - Adds the **`UISystem`** to the ECS world, responsible for handling UI-related logic.
    - **`addScoreSystem`**:
        - Adds the **`ScoreSystem`** to the ECS world, responsible for managing the game score.
    - **`addInputsSystem`**:
        - Adds the **`InputsSystem`** to the ECS world, responsible for handling user inputs.
    - **`addBulletSystem`**:
        - Adds the **`Bullets`** system to the ECS world, responsible for managing bullet entities.
    - **`addWorldMoveSystem`**:
        - Adds the **`WorldMoveSystem`** to the ECS world, responsible for handling world movement.
    - **`addAnimationSystem`**:
        - Adds the **`AnimationSystem`** to the ECS world, responsible for handling entity animations.
    - **`addDeathAnimationSystem`**:
        - Adds the **`DeathAnimationSystem`** to the ECS world, responsible for handling death animations.
    - **`addHealthSystem`**:
        - Adds the **`HealthSystem`** to the ECS world, responsible for managing entity health.
    - **`addBoosterSystem`**:
        - Adds the **`BoosterSystem`** to the ECS world, responsible for managing booster entities.

# Waves.hpp
```cpp
#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

static const std::map<std::string, std::vector<std::pair<size_t, sf::Vector2f>>> enemyPatternMovements = {
    // Weak
    {"WeakUpAndDown", {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}},
    {"WeakLeft", {std::make_pair(800, sf::Vector2f(-100, 1))}},
    {"WeakDiagBotToTop", {std::make_pair(800, sf::Vector2f(-80, 60))}},
    {"WeakDiagTopToBot", {std::make_pair(800, sf::Vector2f(-80, -60))}},

    // Medium
    {"MediumUpAndDown", {std::make_pair(800, sf::Vector2f(-50, 50)), std::make_pair(800, sf::Vector2f(-50, -50))}},
};
```

### **`EnemyPatternMovements` Map:**

1. **Purpose:**
    - The **`enemyPatternMovements`** map stores movement patterns for different enemy types.
    - Each pattern is identified by a unique string key, and the associated value is a vector of pairs.
    - Each pair represents a waypoint in the movement pattern, including the time and position.