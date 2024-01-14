# R-Type/Subscribers Technical Documentation

# Collision.subscriber.hpp
```cpp
#pragma once

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Events/Collision.event.hpp"
#include "R-Type/Components/BaseBullet.component.hpp"

namespace Rtype::Subscriber
{
    class CollisionEventSubscriber : public virtual ECS::EventSubscriber<CollisionEvent>
    {
        public:
            CollisionEventSubscriber()           = default;
            ~CollisionEventSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const CollisionEvent &data) override
            {
                using namespace Engine::Components;

                if (data.movingEntity->has<PlayerComponent>() && data.collidingEntity->has<EnemyComponent>()) {
                    data.movingEntity->removeAllComponents();
                    return;
                }
                if (data.movingEntity->has<BaseBulletComponent>()) {
                    if (data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                        data.collidingEntity->has<PlayerComponent>()) {
                        data.movingEntity->removeAllComponents();
                        data.collidingEntity->removeAllComponents();
                        return;
                    }
                    if (!data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                        data.collidingEntity->has<EnemyComponent>()) {
                        data.movingEntity->removeAllComponents();
                        data.collidingEntity->removeAllComponents();
                        return;
                    }
                }
            }
    };
} // namespace Rtype::Subscriber
```
### **CollisionEventSubscriber Class:**

- **Purpose**: Manages collision event handling within the game.
- **Inherits From**: **`ECS::EventSubscriber<CollisionEvent>`** to handle collision events specifically.
- **Constructor and Destructor**: Default constructor and destructor definitions.
- **Methods**:
    - **`receiveEvent`**: Overrides the base class method to handle collision events.
        - Checks collision scenarios between different entities based on their components.
        - If a player collides with an enemy, it prints "YOU LOSE" and removes all components from the player entity.
        - If a bullet hits a player, it prints "YOU LOSE" and removes all components from both the bullet and player entities.
        - If a bullet hits an enemy, it removes all components from both the bullet and enemy entities.
        - These checks determine the game's outcomes and component removals upon collision events.

This subscriber class encapsulates the logic for collision resolution between various entities, triggering specific actions or outcomes in response to different collision scenarios within the game.

# EnnemyDeath.subscriber.hpp
```cpp
#pragma once

#include "ECS/Components.hpp"
#include "ECS/EventSubscriber.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Position.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Events/EnnemyDeath.event.hpp"

namespace Rtype::Subscriber
{
    class EnnemyDeathSubscriber : public ECS::EventSubscriber<Rtype::Events::EnnemyDeath>
    {
        public:
            EnnemyDeathSubscriber()           = default;
            ~EnnemyDeathSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const Rtype::Events::EnnemyDeath &data) override
            {
                ECS::ComponentHandle<Engine::Components::PositionComponent> position;
                ECS::ComponentHandle<Engine::Components::EnemyComponent>    enemy;

                if (!(data.Enemy->has<Engine::Components::PositionComponent>() &&
                      data.Enemy->has<Engine::Components::EnemyComponent>()))
                    return;

                position = data.Enemy->getComponent<Engine::Components::PositionComponent>();
                enemy    = data.Enemy->getComponent<Engine::Components::EnemyComponent>();
                if (enemy->enemyType == EnemyData::EnemyType::Medium) {
                    WORLD.createEntity(
                        new Engine::Components::PositionComponent(position->x, position->y),
                        new Rtype::Components::BoosterComponent(10),
                        new Engine::Components::RenderableComponent(
                            "./assets/Pickup/PickupIcon-ShieldGenerator-Allaroundshield.png", 0, 0, 1, 0, {2, 2}),
                        new Engine::Components::AnimationComponent(0, 0, 32, 32, 32, 32, 75, 15),
                        new Engine::Components::CollisionComponent(8, 8, 48, 48),
                        new Engine::Components::MovingComponent(
                            {static_cast<float>(position->x), static_cast<float>(position->y)}, 20000, {-1000, 0}));
                }
            }
    };
} // namespace Rtype::Subscriber
```

### **`EnnemyDeathSubscriber` Class:**

1. **Purpose:**
    - Represents a subscriber for the **`EnnemyDeath`** event, responding to the death of an enemy entity.
2. **Inherits From:**
    - **`ECS::EventSubscriber<Rtype::Events::EnnemyDeath>`**
3. **Constructors:**
    - Default Constructor:
        - Initializes an instance of **`EnnemyDeathSubscriber`**.
4. **Member Functions:**
    - **`receiveEvent`**:
        - Overrides the base class method to handle the **`EnnemyDeath`** event.
        - Retrieves the **`PositionComponent`** and **`EnemyComponent`** from the event data.
        - Checks if the enemy entity has the required components.
        - If the enemy type is **`Medium`**, creates a new entity with components for a shield pickup.
5. **Destructor:**
    - Default destructor.

# PlayerMove.subscriber.hpp
```cpp
#pragma once

#include <SFML/Window/Event.hpp>

#include "ECS/EventSubscriber.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"

namespace Rtype::Subscriber
{
    class PlayerMovePressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            PlayerMovePressedSubscriber()           = default;
            ~PlayerMovePressedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyPressedEvent &data) override
            {
                if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                      data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                    return;
                Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                    Engine::EngineClass::getEngine().world().getSystems()["MovePlayer"].get());
                if (!movePlayerSystem) return;
                movePlayerSystem->addMovePlayer(data.keyEvent);
            }
    };

    class PlayerMoveReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
    {
        public:
            PlayerMoveReleasedSubscriber()           = default;
            ~PlayerMoveReleasedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyReleasedEvent &data) override
            {
                if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                      data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                    return;
                Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                    Engine::EngineClass::getEngine().world().getSystems()["MovePlayer"].get());
                if (!movePlayerSystem) return;
                movePlayerSystem->stopMovePlayer(data.keyEvent);
            }
    };
} // namespace Rtype::Subscriber
```
### **PlayerMovePressedSubscriber Class:**

- **Purpose**: Subscribes to key-pressed events related to player movement.
- **Inherits From**: **`ECS::EventSubscriber<KeyPressedEvent>`**.
- **Constructor and Destructor**: Default constructor and destructor definitions.
- **Methods**:
    - **`receiveEvent`**: Overrides the base class method to handle key-pressed events.
        - Verifies if the received key event corresponds to movement keys (W, A, S, D).
        - Accesses the **`MovePlayer`** system to initiate player movement based on the received key event.

### **PlayerMoveReleasedSubscriber Class:**

- **Purpose**: Subscribes to key-released events related to player movement.
- **Inherits From**: **`ECS::EventSubscriber<KeyReleasedEvent>`**.
- **Constructor and Destructor**: Default constructor and destructor definitions.
- **Methods**:
    - **`receiveEvent`**: Overrides the base class method to handle key-released events.
        - Checks if the received key event corresponds to movement keys (W, A, S, D).
        - Accesses the **`MovePlayer`** system to halt player movement based on the released key event.

These subscriber classes handle the registration and processing of key events associated with player movement, ensuring that movement actions are triggered or stopped correctly within the game. They interface with the **`MovePlayer`** system to manage player movement based on the key events received.

# ShootPlayer.subscriber.hpp
```cpp
#pragma once

#include <SFML/Window/Event.hpp>

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/LayeredRenderable.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/Components/WeaponType.component.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"
#include "SFML/System/Clock.hpp"

namespace Rtype::Subscriber
{
    static sf::Clock *_shared_clock = new sf::Clock();
    static bool       _reset        = false;

    class ChangeWeapon : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            ChangeWeapon() : _clock(){};
            ~ChangeWeapon() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyPressedEvent &data) override
            {
                if (!(_clock.getElapsedTime().asMilliseconds() >= 200 && data.keyEvent.code == sf::Keyboard::R)) return;
                auto player = WORLD.getEntityWithComponents<
                    Engine::Components::PositionComponent, Engine::Components::LayeredRenderableComponent,
                    Engine::Components::PlayerComponent, Components::WeaponTypeComponent>();

                if (!player) return;
                auto weapon = player->getComponent<Components::WeaponTypeComponent>();
                auto render = player->getComponent<Engine::Components::LayeredRenderableComponent>();
                weapon->reset(weapon->type == Components::WeaponType::BASIC ? Components::WeaponType::BIG
                                                                            : Components::WeaponType::BASIC);
                render->renderable[1]->isDisplayed = weapon->type == Components::WeaponType::BIG;
                render->renderable[2]->isDisplayed = weapon->type == Components::WeaponType::BASIC;
                _clock.restart();
            }

        private:
            sf::Clock _clock;
    };

    class ShootPlayerPressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            ShootPlayerPressedSubscriber() : _clock(){};
            ~ShootPlayerPressedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string     &name,
                              [[maybe_unused]] const KeyPressedEvent &data) override
            {
                if (data.keyEvent.code == sf::Keyboard::Space && _reset) {
                    _shared_clock->restart();
                    _reset = false;
                }
            }

        private:
            sf::Clock _clock;
    };

    class ShootPlayerReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
    {
        public:
            ShootPlayerReleasedSubscriber() : _clock(){};
            ~ShootPlayerReleasedSubscriber() override = default;

            void receiveEvent([[maybe_unused]] const std::string &name, const KeyReleasedEvent &data) override
            {
                using namespace Engine::Components;

                if (data.keyEvent.code != sf::Keyboard::Space) return;
                Engine::System::MovePlayer *movePlayerSystem =
                    dynamic_cast<Engine::System::MovePlayer *>(WORLD.getSystems()["MovePlayer"].get());
                Engine::System::Bullets *bulletsSystem =
                    dynamic_cast<Engine::System::Bullets *>(WORLD.getSystems()["BulletsSystem"].get());

                std::vector<ECS::Entity *> players = WORLD.getEntitiesWithComponents<PlayerComponent>();
                ECS::Entity               *player  = nullptr;
                for (auto &p : players) {
                    if (p->getComponent<PlayerComponent>()->playerNb ==
                        Engine::EngineClass::getEngine().getCurrentPlayer()) {
                        player = p;
                        break;
                    }
                }

                if (!player || !movePlayerSystem) return;

                if (!player->has<Engine::Components::PositionComponent, Engine::Components::RenderableComponent,
                                 Components::WeaponTypeComponent>())
                    return;
                ECS::ComponentHandle<Engine::Components::PositionComponent> pos =
                    player->getComponent<Engine::Components::PositionComponent>();
                ECS::ComponentHandle<Engine::Components::RenderableComponent> rend =
                    player->getComponent<Engine::Components::RenderableComponent>();
                ECS::ComponentHandle<Components::WeaponTypeComponent> weapon =
                    player->getComponent<Components::WeaponTypeComponent>();
                fire(pos, rend, weapon, bulletsSystem);
                _reset = true;
            }

        private:
            sf::Clock _clock;

            void fire(ECS::ComponentHandle<Engine::Components::PositionComponent>   &pos,
                      ECS::ComponentHandle<Engine::Components::RenderableComponent> &rend,
                      ECS::ComponentHandle<Components::WeaponTypeComponent>         &weapon,
                      Engine::System::Bullets                                       *bulletsSystem)
            {
                switch (weapon->type) {
                    case Components::BASIC:
                        if (_clock.getElapsedTime().asMilliseconds() < Components::rateOfFireLst[Components::BASIC])
                            return;
                        bulletsSystem->spawnBullet(
                            false, static_cast<float>(pos->x + static_cast<int>(rend->size.x / 2) - 20),
                            static_cast<float>(pos->y + static_cast<int>(rend->size.x / 2) - 2), {1000, 0}, 200, 50);
                        break;
                    case Components::BIG:
                        if (_clock.getElapsedTime().asMilliseconds() < Components::rateOfFireLst[Components::BIG])
                            return;
                        bulletsSystem->spawnBigBullet(
                            false, static_cast<float>(pos->x + static_cast<int>(rend->size.x / 2) - 54),
                            static_cast<float>(pos->y + static_cast<int>(rend->size.x / 2) - 16), {1000, 0}, 200, 0,
                            200);
                        break;
                }
                _clock.restart();
            }
    };
} // namespace Rtype::Subscriber
```

### **`ChangeWeapon` Class:**

1. **Purpose:**
    - Responds to **`KeyPressed`** events, specifically for the "R" key, to change the player's weapon type.
2. **Inherits From:**
    - **`ECS::EventSubscriber<KeyPressedEvent>`**
3. **Constructors:**
    - Initializes the class, including the clock used to control the firing rate.
4. **Member Functions:**
    - **`receiveEvent`**:
        - Overrides the base class method to handle **`KeyPressed`** events.
        - Checks if the "R" key is pressed and enough time has passed since the last change.
        - Retrieves the player entity and its **`WeaponTypeComponent`**.
        - Resets the weapon type and updates the display of associated renderables.
        - Restarts the clock.

### **`ShootPlayerPressedSubscriber` Class:**

1. **Purpose:**
    - Responds to **`KeyPressed`** events, specifically for the spacebar key, to initiate shooting.
2. **Inherits From:**
    - **`ECS::EventSubscriber<KeyPressedEvent>`**
3. **Constructors:**
    - Initializes the class, including the clock used to track time since the last shot.
4. **Member Functions:**
    - **`receiveEvent`**:
        - Overrides the base class method to handle **`KeyPressed`** events.
        - Checks if the spacebar key is pressed and resets the shared clock.

### **`ShootPlayerReleasedSubscriber` Class:**

1. **Purpose:**
    - Responds to **`KeyReleased`** events, specifically for the spacebar key, to stop shooting.
2. **Inherits From:**
    - **`ECS::EventSubscriber<KeyReleasedEvent>`**
3. **Constructors:**
    - Initializes the class, including the clock used to track time since the last shot.
4. **Member Functions:**
    - **`receiveEvent`**:
        - Overrides the base class method to handle **`KeyReleased`** events.
        - Checks if the spacebar key is released and triggers the firing logic based on the player's weapon type.
        - Resets the shared clock.