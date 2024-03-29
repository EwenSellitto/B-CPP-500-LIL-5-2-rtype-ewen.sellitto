/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Entities.hpp
*/

#pragma once

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
                                                    bool isValid = inputsSystem.handleSend({"PORT", "IP"});
                                                    if (isValid) uiSystem.handleGoWaitingClient();
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
        std::string str = "Nombre de joueurs : " + std::to_string(NETWORK.getWaitingRoom().getPlayers().size()) + "/4";
        world->createEntity(new TextComponent(str, font, 30, {310, 180}, false, true, "nbPlayers"));
        std::string strServer = "Server IP : " + NETWORK.getIP().toString();
        world->createEntity(new TextComponent(strServer, font, 30, {310, 280}, false, true));
        std::string strPort = "Port : " + std::to_string(NETWORK.getPort());
        world->createEntity(new TextComponent(strPort, font, 30, {310, 380}, false, true));
        world->createEntity(
            new PositionComponent(40, 100), new MenuComponent(),
            new ButtonComponent("Pause Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleGoCreate();
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
        Engine::EngineClass &engine    = Engine::EngineClass::getEngine();
        std::string          strServer = "Server IP : " + engine.network().getIP().toString();
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
                                                    bool isValid = inputsSystem.handleSend({"PORT"});
                                                    if (isValid) uiSystem.handleGoWaitingHost();
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
        ECS::id_t newEntity =
            world->createEntity(new TextComponent("Game over", font, 80, {400, 50}, sf::Color::White, true));
        for (auto &i : world->getMutEntity(newEntity).getComponents())
            i.second->setHasChanged(false);
        newEntity = world->createEntity(
            new PositionComponent(400, 325), new TextComponent("Restart", font, 40, {400, 300}, true, true),
            new ButtonComponent("Restart",
                                [world]() {
                                    NETWORK.resetServer();
                                    NETWORK.startServer(5555, true);
                                    // sleep 200 ms
                                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                                    NETWORK.setIsReadyToStart(true);
                                }),
            new RenderableComponent("./assets/menu/button_long/long_on.png", 0, 0, 3, 0, {2, 2}, true));
        for (auto &i : world->getMutEntity(newEntity).getComponents())
            i.second->setHasChanged(false);
        newEntity = world->createEntity(
            new PositionComponent(400, 410), new TextComponent("Menu", font, 40, {400, 385}, true, true),
            new ButtonComponent("Menu",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleGoMenu();
                                    NETWORK.resetServer();
                                }),
            new RenderableComponent("./assets/menu/button_long/long_on.png", 0, 0, 3, 0, {2, 2}, true));
        for (auto &i : world->getMutEntity(newEntity).getComponents())
            i.second->setHasChanged(false);
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
        auto StrongUpAndDown = enemyPatternMovements.find("StrongUpAndDown");

        world->createEntity(new EnemyQueueComponent({

            // twin snake 1
            std::make_pair(false, std::make_pair(std::make_tuple(160, 200, true, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(170, 210, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(180, 220, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(190, 230, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(200, 240, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(210, 250, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(220, 260, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(230, 270, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(240, 280, false, WeakUpAndDown->second), 0)),

            // twin snake 2
            std::make_pair(false, std::make_pair(std::make_tuple(160, 350, true, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(170, 360, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(180, 370, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(190, 380, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(200, 390, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(210, 400, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(220, 410, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(230, 420, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(240, 430, false, WeakUpAndDown->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(350, 300, true, MediumUpAndDown->second), 1)),

            // random movements
            std::make_pair(false, std::make_pair(std::make_tuple(500, 450, true, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(540, 480, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(580, 450, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(600, 480, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(620, 450, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(640, 480, false, WeakUpAndDown->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(720, 420, true, MediumUpAndDown->second), 1)),

            // wall
            std::make_pair(false, std::make_pair(std::make_tuple(800, 140, true, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(800, 160, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(800, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(800, 200, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(800, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(800, 240, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(800, 260, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(800, 280, false, WeakLeft->second), 0)),

            // snake
            std::make_pair(false, std::make_pair(std::make_tuple(960, 400, true, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(970, 410, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(980, 420, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(990, 430, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1000, 440, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1010, 450, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1020, 460, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1030, 470, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1040, 480, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1050, 490, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1060, 500, false, WeakUpAndDown->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1070, 510, false, WeakUpAndDown->second), 0)),

            // cross
            // vertical
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 140, true, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 160, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 200, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 240, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 260, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 280, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1200, 300, false, WeakLeft->second), 0)),
            // horizontal
            std::make_pair(false, std::make_pair(std::make_tuple(1160, 220, true, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1170, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1180, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1190, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1210, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1220, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1230, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1240, 220, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(1100, 420, true, MediumUpAndDown->second), 1)),

            // obstacles walls
            // top wall
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 40, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 80, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 120, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 160, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 200, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 240, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 280, false, WeakLeft->second), 3)),
            // bottom wall
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 400, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 440, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 480, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 520, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 560, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 600, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1300, 640, false, WeakLeft->second), 3)),

            // diagonal pass through (top - bottom)
            std::make_pair(false, std::make_pair(std::make_tuple(500, 40, true, WeakDiagBotToTop->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(520, 50, false, WeakDiagBotToTop->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(540, 60, false, WeakDiagBotToTop->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(560, 70, false, WeakDiagBotToTop->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(580, 80, false, WeakDiagBotToTop->second), 0)),

            // diagonal pass through (bottom - top)
            std::make_pair(false, std::make_pair(std::make_tuple(1600, 600, true, WeakDiagTopToBot->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1620, 590, false, WeakDiagTopToBot->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1640, 580, false, WeakDiagTopToBot->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1660, 570, false, WeakDiagTopToBot->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1680, 560, false, WeakDiagTopToBot->second), 0)),

            // diagonal pass through (top - bottom)
            std::make_pair(false, std::make_pair(std::make_tuple(1700, 40, true, WeakDiagBotToTop->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1720, 50, false, WeakDiagBotToTop->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1740, 60, false, WeakDiagBotToTop->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1760, 70, false, WeakDiagBotToTop->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1780, 80, false, WeakDiagBotToTop->second), 0)),

            // diagonal pass through (bottom - top)
            std::make_pair(false, std::make_pair(std::make_tuple(1800, 600, true, WeakDiagTopToBot->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1820, 590, false, WeakDiagTopToBot->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1840, 580, false, WeakDiagTopToBot->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1860, 570, false, WeakDiagTopToBot->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(1880, 560, false, WeakDiagTopToBot->second), 0)),

            // 1st wall
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 40, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 80, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 120, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 260, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 300, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 340, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 380, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 420, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 560, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 600, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(1980, 640, false, WeakLeft->second), 3)),

            // 2nd wall
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 40, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 80, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 120, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 160, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 300, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 340, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 380, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 520, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 560, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 600, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2005, 640, false, WeakLeft->second), 3)),

            // 3rd wall
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 40, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 80, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 120, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 160, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 300, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 340, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 380, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 520, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 560, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 600, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2030, 640, false, WeakLeft->second), 3)),

            // 4th wall
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 40, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 80, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 120, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 260, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 300, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 340, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 380, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 420, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 560, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 600, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2050, 640, false, WeakLeft->second), 3)),

            // 5th wall
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 40, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 80, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 220, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 260, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 300, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 340, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 380, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 420, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 460, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 600, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2075, 640, false, WeakLeft->second), 3)),

            // 6th wall
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 40, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 80, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 220, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 260, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 300, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 340, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 380, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 420, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 460, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 600, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2100, 640, false, WeakLeft->second), 3)),

            // 7th wall
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 40, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 80, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 220, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 260, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 300, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 340, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 380, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 420, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 460, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 600, false, WeakLeft->second), 3)),
            std::make_pair(false, std::make_pair(std::make_tuple(2125, 640, false, WeakLeft->second), 3)),

            // R letter
            // std::make_pair(false, std::make_pair(std::make_tuple(2200, 140, true, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2420, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2440, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2460, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2480, 140, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2400, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2400, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2400, 260, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2400, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2420, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2440, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2460, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2480, 300, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2500, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2500, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2500, 260, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2400, 340, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2400, 380, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2400, 420, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2400, 460, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2440, 340, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2460, 380, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2480, 420, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2500, 460, false, WeakLeft->second), 0)),

            // '-' letter
            std::make_pair(false, std::make_pair(std::make_tuple(2550, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2570, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2590, 300, false, WeakLeft->second), 0)),

            // T letter
            std::make_pair(false, std::make_pair(std::make_tuple(2620, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2640, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2660, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2680, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2700, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2720, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2740, 140, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2680, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2680, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2680, 260, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2680, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2680, 340, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2680, 380, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2680, 420, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2680, 460, false, WeakLeft->second), 0)),

            // Y letter
            std::make_pair(false, std::make_pair(std::make_tuple(2780, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2780, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2800, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2800, 260, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2860, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2860, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2840, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2840, 260, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2820, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2820, 340, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2820, 380, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2820, 420, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2820, 460, false, WeakLeft->second), 0)),

            // P letter
            std::make_pair(false, std::make_pair(std::make_tuple(2900, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2920, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2940, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2960, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2980, 140, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2900, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2900, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2900, 260, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2900, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2920, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2940, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2960, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2980, 300, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(3000, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3000, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3000, 260, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(2900, 340, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2900, 380, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2900, 420, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(2900, 460, false, WeakLeft->second), 0)),

            // E letter
            std::make_pair(false, std::make_pair(std::make_tuple(3040, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3060, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3080, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3100, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3120, 140, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3140, 140, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(3040, 180, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3040, 220, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3040, 260, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3040, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3040, 340, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3040, 380, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3040, 420, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3040, 460, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(3060, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3080, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3100, 300, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3120, 300, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(3060, 460, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3080, 460, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3100, 460, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3120, 460, false, WeakLeft->second), 0)),
            std::make_pair(false, std::make_pair(std::make_tuple(3140, 460, false, WeakLeft->second), 0)),

            std::make_pair(false, std::make_pair(std::make_tuple(3250, 100, true, StrongUpAndDown->second), 2)),
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
