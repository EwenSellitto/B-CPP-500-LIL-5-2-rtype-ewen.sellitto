/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Entities.hpp
*/

#pragma once

#include <iostream>
#include <sstream>

#include "ECS/World.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Cursor.component.hpp"
#include "Engine/Components/ExcludeCollision.component.hpp"
#include "Engine/Components/LayeredAnimation.component.hpp"
#include "Engine/Components/LayeredRenderable.component.hpp"
#include "Engine/Components/Menu.component.hpp"
#include "Engine/Components/Music.component.hpp"
#include "Engine/Components/Options.component.hpp"
#include "Engine/Components/Parallax.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Speed.component.hpp"
#include "Engine/Components/Text.component.hpp"
#include "Engine/Components/TextInput.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
#include "Engine/Systems/Inputs.system.hpp"
#include "Engine/Systems/Options.system.hpp"
#include "Engine/Systems/Sound.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
#include "R-Type/Components/EnemyMovements.component.hpp"
#include "R-Type/Components/EnemyQueue.component.hpp"
#include "R-Type/Components/Health.component.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/GameWorld/EnemyMakers.hpp"

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
        std::vector<std::pair<int, int>> playerPos = {{100, 300}, {100, 360}, {100, 300}, {100, 400}};

        world->createEntity(
            new PlayerComponent(playerNb), new PositionComponent(playerPos[playerNb].first, playerPos[playerNb].second),
            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 2, 90),
            new LayeredRenderableComponent(
                1,
                new RenderableComponent("./assets/MainShip/MainShip-Engines-BaseEngine-Powering.png", 0, 0, 1, 90,
                                        {1, 1}, false),
                new RenderableComponent("./assets/MainShip/MainShip-Weapons-Rockets-Croped.png", 0, 0, 1, 90),
                new RenderableComponent("./assets/MainShip/MainShip-Engines-BaseEngine.png", 0, 0, 1, 90)),
            new LayeredAnimationComponent(new AnimationComponent(0, 0, 48, 48, 48, 48, 100, 4)),
            new CollisionComponent(9, 11, 30, 26), new SpeedComponent(150));
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
            new MenuComponent(),
            new ButtonComponent("Start Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleStartGame();
                                }),
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
        // std::string          str    = "Nombre de joueurs : " + std::to_string(engine.getPlayersAmount()) + "/4";
        // world->createEntity(new TextComponent(str, font, 30, {310, 180}, false, true));
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
                                }),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(30, 100), new MenuComponent(),
                            new RenderableComponent("./assets/menu/icons/close_icon.png", 0, 0, 2, 0, {2, 2}, true));
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
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleStartGame();
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

        world->createEntity(
            new EnemyQueueComponent({std::make_pair(false, std::make_pair(std::make_tuple(100, 50, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(150, 60, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(200, 70, true), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(250, 80, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(300, 90, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(350, 100, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(400, 300, true), 1))}));
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
