// Entities.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/ExcludeCollision.component.hpp"
#include "Engine/Components/Music.component.hpp"
#include "Engine/Components/Parallax.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Speed.component.hpp"
#include "Engine/Components/Text.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
#include "Engine/Systems/Sound.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
#include "R-Type/Components/EnemyMovements.component.hpp"
#include "R-Type/Components/EnemyQueue.component.hpp"
#include "R-Type/Components/Player.component.hpp"

namespace Entities
{
    inline void createViewEntity(ECS::World *world)
    {
        world->createEntity(new Engine::Components::ViewComponent());
    }

    inline void createPlayerEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        world->createEntity(new PlayerComponent(), new PositionComponent(100, 100),
                            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1, 0),
                            new CollisionComponent(9, 11, 30, 26), new TypeComponent(TypeComponent::player),
                            new SpeedComponent(150));
    }
    void createMenuEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font_big.ttf")) {
            return;
        }

        world->createEntity(new TextComponent("Options", font, 80, {550, 50}, sf::Color::White, false));
        world->createEntity(new RenderableComponent("./assets/menu/panel/options.png", 0, 0, 1, 0, {2, 2}, true),
                            new PositionComponent(450, 300));
        world->createEntity(
            new PositionComponent(360, 300), new TextComponent("vsync", font, 40, {250, 300}),
            new ButtonComponent("vsync",
                                [world]() {
                                    Engine::System::Sound SoundSystem = Engine::System::Sound(*world);
                                    SoundSystem.UpVolumeMusic();
                                }),
            new RenderableComponent("./assets/menu/button_check/check_off.png", 0, 0, 3, 0, {2, 2}, false));
        world->createEntity(
            new PositionComponent(650, 300), new TextComponent("FullScreen", font, 40, {520, 300}),
            new ButtonComponent("FullScreen",
                                [world]() {
                                    Engine::System::Sound SoundSystem = Engine::System::Sound(*world);
                                    SoundSystem.DownVolumeMusic();
                                }),
            new RenderableComponent("./assets/menu/button_check/check_off.png", 0, 0, 3, 0, {2, 2}, false));
        world->createEntity(new PositionComponent(250, 450), new TextComponent("musique", font, 40, {250, 400}),
                            new RenderableComponent("./assets/menu/range/barre_pleine.png", 0, 0, 3, 0, {2, 2}, false));
        world->createEntity(new PositionComponent(520, 450), new TextComponent("SFX", font, 40, {520, 400}),
                            new RenderableComponent("./assets/menu/range/barre_pleine.png", 0, 0, 3, 0, {2, 2}, false));
        world->createEntity(new MusicComponent("./assets/Music/MusicMenu.ogg"));
    }

    void createButtonEntities(ECS::World *world)
    {
        using namespace Engine::Components;
        sf::Font font;
        if (!font.loadFromFile("./assets/fonts/font_big.ttf")) {
            return;
        }
        world->createEntity(new TextComponent("R-Type", font, 110, {300, 50}));

        world->createEntity(
            new PositionComponent(400, 370), new TextComponent("Quit", font, 40, {375, 340}),
            new ButtonComponent("Quit",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleQuitGame();
                                }),
            new RenderableComponent("./assets/menu/button_long/long_off.png", 0, 0, 1, 0, {2, 2}, true));

        world->createEntity(
            new PositionComponent(400, 270), new TextComponent("Start", font, 40, {370, 240}),
            new ButtonComponent("Start Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleStartGame();
                                }),
            new RenderableComponent("./assets/menu/button_long/long_off.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(
            new PositionComponent(40, 100),
            new ButtonComponent("Pause Game",
                                [world]() {
                                    Engine::System::UI uiSystem = Engine::System::UI(*world);
                                    uiSystem.handleStartGame();
                                }),
            new RenderableComponent("./assets/menu/button_tabs/button_main_disabled.png", 0, 0, 1, 0, {2, 2}, true));
        world->createEntity(new PositionComponent(30, 100),
                            new RenderableComponent("./assets/menu/icons/settings_icon.png", 0, 0, 2, 0, {2, 2}, true));
    }

    void createBackground(ECS::World *world, const std::string &texturePath, ParallaxLayer layer, float speed,
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

    size_t basicEnemyMaker(float y, bool isAttacking)
    {
        using namespace Engine::Components;

        ECS::World &world       = Engine::EngineClass::getEngine().world();
        auto        attributes  = EnemyData::enemyTypeAttributes.at(EnemyData::EnemyType::Weak);
        size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
        id_t enemyId = world.createEntity(new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
                                          new RenderableComponent(attributes.spritePath, 20, 20, 0),
                                          new EnemyComponent(attributes.health, EnemyData::EnemyType::Weak),
                                          new CollisionComponent(21, 23, 22, 22), new ExcludeCollisionComponent(0));

        ECS::Entity &enemy = world.getMutEntity(enemyId);

        if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

        enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
            {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
        return enemyId;
    }

    inline void createEnemyQueue(ECS::World *world)
    {
        using namespace Engine::Components;

        world->createEntity(new EnemyQueueComponent(
            {std::make_pair(false, std::make_pair(std::make_tuple(100, 50, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(150, 60, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(200, 70, true), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(250, 80, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(300, 90, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(350, 100, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(400, 110, true), basicEnemyMaker))}));
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
