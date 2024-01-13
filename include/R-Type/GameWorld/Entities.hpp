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
#include "Engine/Components/Type.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
#include "Engine/Systems/Options.system.hpp"
#include "Engine/Systems/Sound.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
#include "R-Type/Components/EnemyMovements.component.hpp"
#include "R-Type/Components/EnemyQueue.component.hpp"
#include "R-Type/Components/Health.component.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "Waves.hpp"

namespace Entities
{
    inline void createViewEntity(ECS::World *world)
    {
        world->createEntity(new Engine::Components::ViewComponent());
    }

    inline void createPlayerEntities(ECS::World *world)
    {
        using namespace Engine::Components;

        world->createEntity(
            new PlayerComponent(), new PositionComponent(100, 100),
            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 2, 90),
            new LayeredRenderableComponent(
                1,
                new RenderableComponent("./assets/MainShip/MainShip-Engines-BaseEngine-Powering.png", 0, 0, 1, 90,
                                        {1, 1}, false),
                new RenderableComponent("./assets/MainShip/MainShip-Weapons-Rockets-Croped.png", 0, 0, 1, 90),
                new RenderableComponent("./assets/MainShip/MainShip-Engines-BaseEngine.png", 0, 0, 1, 90)),
            new LayeredAnimationComponent(new AnimationComponent(0, 0, 48, 48, 48, 48, 100, 4)),
            new CollisionComponent(9, 11, 30, 26), new TypeComponent(TypeComponent::player), new SpeedComponent(150));
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
            new ButtonComponent(
                "vsync",
                [world]() { Engine::System::OptionsSystem optionsSystem = Engine::System::OptionsSystem(*world); },
                false),
            new OptionsComponent(),
            new RenderableComponent("./assets/menu/button_check/check_off.png", 0, 0, 3, 0, {2, 2}, false, false));
        world->createEntity(
            new PositionComponent(650, 300), new TextComponent("FullScreen", font, 40, {520, 300}, false, false),
            new ButtonComponent(
                "FullScreen",
                [world]() {
                    Engine::System::Sound SoundSystem = Engine::System::Sound(*world);
                    SoundSystem.DownVolumeMusic();
                },
                false),
            new OptionsComponent(),
            new RenderableComponent("./assets/menu/button_check/check_off.png", 0, 0, 3, 0, {2, 2}, false, false));
        world->createEntity(
            new PositionComponent(250, 450), new TextComponent("musique", font, 40, {250, 400}, false, false),
            new RenderableComponent("./assets/menu/range/barre_pleine.png", 0, 0, 3, 0, {2, 2}, false, false),
            new OptionsComponent()); // size x= 240 y=25
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
        world->createEntity(new TextComponent("R-Type", font, 110, {300, 50}), new MenuComponent());

        world->createEntity(
            new PositionComponent(400, 370), new TextComponent("Quit", font, 40, {375, 340}), new MenuComponent(),
            new ButtonComponent("Quit",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleQuitGame();
                                }),
            new RenderableComponent("./assets/menu/button_long/long_off.png", 0, 0, 1, 0, {2, 2}, true));

        world->createEntity(
            new PositionComponent(400, 270), new TextComponent("Start", font, 40, {370, 240}), new MenuComponent(),
            new ButtonComponent("Start Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleStartGame();
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
            world->createEntity(new PositionComponent(0, 0), renderable, new ParallaxComponent(layer, speed));
        } else {
            renderable->position = {trueSize.x, 0};
            world->createEntity(new PositionComponent(trueSize.x, 0), renderable, new ParallaxComponent(layer, speed));
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
            new PositionComponent(40, 100), new MenuComponent(), new ButtonComponent("Pause Game", [&]() {}),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 39, 0, {2, 2}, true));
        world->createEntity(
            new PositionComponent(30, 100), new MenuComponent(),
            new RenderableComponent("./assets/menu/icons/settings_icon.png", 0, 0, 40, 0, {2, 2}, true));
        // world->createEntity(
        //     new PositionComponent(position.x, position.y),
        //     new TextComponent(sceneName, font, 40, {position.x, position.y}, true, false),
        //     new OptionsComponent(),
        //     new ButtonComponent(sceneName,
        //         []() {
        //             std::cout << "back to menu" << std::endl;
        //         }),
        //     new RenderableComponent(texturePath, 0, 0, 3, 0, {2, 2}, true, false));
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

    inline size_t basicEnemyMaker(float y, bool isAttacking,
                                  std::vector<std::pair<size_t, sf::Vector2f>> PatternMovements)
    {
        using namespace Engine::Components;
        using namespace Rtype::Components;

        ECS::World &world       = Engine::EngineClass::getEngine().world();
        size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
        ECS::id_t   enemyId     = world.createEntity(
            new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
            new RenderableComponent("Klaed-Scout-Base"), new EnemyComponent(EnemyData::EnemyType::Weak),
            new CollisionComponent("Klaed-Scout-Base"), new ExcludeCollisionComponent(0), new HealthComponent(20));

        ECS::Entity &enemy = world.getMutEntity(enemyId);

        if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

        enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
            // {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
            PatternMovements));

        return enemyId;
    }

    inline size_t mediumEnemyMaker(float y, bool isAttacking)
    {
        using namespace Engine::Components;
        using namespace Rtype::Components;

        ECS::World &world       = Engine::EngineClass::getEngine().world();
        size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
        ECS::id_t   enemyId     = world.createEntity(
            new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
            new RenderableComponent("Klaed-Battlecruiser-Base"), new EnemyComponent(EnemyData::EnemyType::Medium),
            new CollisionComponent("Klaed-Battlecruiser-Base"), new ExcludeCollisionComponent(0),
            new HealthComponent(120));

        ECS::Entity &enemy = world.getMutEntity(enemyId);

        if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

        if (static_cast<float>(enemy.getComponent<PositionComponent>()->x) > 800) {
            std::cout << (enemy.getComponent<PositionComponent>()->x) << std::endl;
            enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
                {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
        } else {
            std::cout << (enemy.getComponent<PositionComponent>()->x) << std::endl;
            enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
                {std::make_pair(800, sf::Vector2f(-50, 50)), std::make_pair(800, sf::Vector2f(-50, -50))}));
        }
        return enemyId;
    }

    inline size_t strongEnemyMaker(float y, bool isAttacking)
    {
        using namespace Engine::Components;
        using namespace Rtype::Components;

        ECS::World &world       = Engine::EngineClass::getEngine().world();
        size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
        ECS::id_t   enemyId     = world.createEntity(
            new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
            new RenderableComponent("Klaed-Dreadnought-Base"), new EnemyComponent(EnemyData::EnemyType::Strong),
            new CollisionComponent("Klaed-Dreadnought-Base"), new ExcludeCollisionComponent(0),
            new HealthComponent(400));

        ECS::Entity &enemy = world.getMutEntity(enemyId);

        if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

        // enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
        //     {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
        return enemyId;
    }

    inline void createEnemyQueue(ECS::World *world)
    {
        using namespace Engine::Components;

        // world->createEntity(new EnemyQueueComponent({TwinSnake(10,10)}));

        //     auto UpAndDown = enemyPatternMovements.find("UpAndDown");
        //     world->createEntity(new EnemyQueueComponent({
        //         // twin snake 1
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(160, 200, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(170, 210, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(180, 220, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(190, 230, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(200, 240, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(210, 250, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(220, 260, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),

        //         // twin snake 2
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(160, 350, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(170, 360, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(180, 370, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(190, 380, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(200, 390, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(210, 400, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(220, 410, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),

        //         std::make_pair(false, std::make_pair(std::make_tuple(350, 300, true), mediumEnemyMaker)),

        //         // random movements
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(500, 450, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(540, 480, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(580, 450, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(600, 480, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(620, 450, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(640, 480, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),

        //         std::make_pair(false, std::make_pair(std::make_tuple(660, 420, true), mediumEnemyMaker)),

        //         // wall
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(800, 140, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(800, 160, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(800, 180, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(800, 200, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(800, 220, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(800, 240, false), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(800, 260, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),
        //         std::make_pair(
        //             false, std::make_pair(std::make_tuple(800, 280, true), basicEnemyMaker(0, false,
        //             UpAndDown->second))),

        //         // std::make_pair(false, std::make_pair(std::make_tuple(180, 370, true), basicEnemyMaker(0, false,
        //         // UpAndDown->second))),

        //         // std::make_pair(false, std::make_pair(std::make_tuple(700, 350, true), strongEnemyMaker)),
        //     }));
    }

    inline void createWorldMoveProgress(ECS::World *world)
    {
        using namespace Engine::Components;

        using namespace Engine::Components;

        auto   now         = std::chrono::high_resolution_clock::now();
        auto   epoch       = now.time_since_epoch();
        size_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

        world->createEntity(new WorldMoveProgressComponent(currentTime, 0, 50));
    }
} // namespace Entities
