# R-Type/GameWorld Technical Documentation

# Entities.hpp
```cpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/ExcludeCollision.component.hpp"
#include "Engine/Components/Parallax.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Speed.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
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

        ECS::id_t ship_id = world->createEntity(
            new PlayerComponent(), new PositionComponent(100, 100),
            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1, 0),
            new CollisionComponent(9, 11, 30, 26), new TypeComponent(TypeComponent::player), new SpeedComponent(150));
    }

    inline void createButtonEntities(ECS::World *world)
    {
        using namespace Engine::Components;

        auto startButtonEntity = world->createEntity(
            new ButtonComponent("Start Game", []() { std::cout << "Start Game" << std::endl; }),
            new PositionComponent(100, 100),
            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1, 0, {1, 1}, true));
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

    inline size_t basicEnemyMaker(float y, bool isAttacking)
    {
        using namespace Engine::Components;

        ECS::World &world       = Engine::EngineClass::getEngine().world();
        auto        attributes  = EnemyData::enemyTypeAttributes.at(EnemyData::EnemyType::Weak);
        size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
        ECS::id_t   enemyId =
            world.createEntity(new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
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
```
### **Functionality:**

### **`createViewEntity`**

- Creates an entity representing the view.

### **`createPlayerEntities`**

- Generates player entities with components for rendering, position, collision, type, and speed.

### **`createButtonEntities`**

- Creates button entities with components for button functionality, position, and renderable attributes.

### **`createBackground`**

- Generates entities representing background layers with parallax effects using renderable, position, and parallax components.

### **`createParallax`**

- Creates multiple background entities with different parallax layers and textures.

### **`basicEnemyMaker`**

- Generates a basic enemy entity with various components based on parameters like position, renderable attributes, health, collision, and attack attributes.

### **`createEnemyQueue`**

- Creates entities for an enemy queue with specific attributes for enemy creation.

### **`createWorldMoveProgress`**

- Creates an entity to track the progress of the world's movement.

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
#include "R-Type/Subscribers/Collision.subscriber.hpp"
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

        world->subscribe<KeyPressedEvent>(subMovePressed);
        world->subscribe<KeyReleasedEvent>(subMoveReleased);
        world->subscribe<CollisionEvent>(subCollision);
        world->subscribe<KeyReleasedEvent>(subShootPlayer);
        world->subscribe<KeyPressedEvent>(subShootPlayer2);
    }
} // namespace Subscribers
```
### **`subscribeToEvents`**

- Initializes different event subscribers for specific events within the game.
- Creates instances of various event subscribers for actions like player movement (pressed and released), collisions, and shooting.
- Subscribes these subscribers to their corresponding events in the ECS world for handling key presses, collisions, and shooting actions.

This setup allows the ECS world to effectively handle different types of events by routing them to their respective event subscribers, enabling precise control and reaction to key actions, collisions, and shooting mechanics within the game.

# Systems.hpp
```cpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Systems/Animation.system.hpp"
#include "Engine/Systems/Parallax.system.hpp"
#include "Engine/Systems/Physics.system.hpp"
#include "Engine/Systems/Renderer.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "Engine/Systems/WorldMove.system.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "R-Type/Systems/Enemy.system.hpp"
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
} // namespace Systems
```
### **System Addition Functions:**

- **`addRenderer`**: Adds a renderer system to the ECS world.
- **`addPhysics`**: Adds a physics system to the ECS world.
- **`addPlayerMovement`**: Adds a player movement system to the ECS world.
- **`addEnemySystem`**: Adds an enemy system to the ECS world.
- **`addParallaxSystem`**: Adds a parallax system to the ECS world.
- **`addUISystem`**: Adds a UI system to the ECS world.
- **`addBulletSystem`**: Adds a bullet system to the ECS world.
- **`addWorldMoveSystem`**: Adds a world movement system to the ECS world.
- **`addAnimationSystem`**: Adds an animation system to the ECS world.

These functions facilitate the organization and incorporation of various systems into the ECS world. Each system is responsible for managing specific aspects of the game logic, such as rendering, physics, player movement, enemy behavior, UI interactions, bullets, world movement, and animations. This modular approach helps in maintaining a structured and efficient architecture for the game's functionality and behavior.