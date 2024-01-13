# R-Type/Subscribers Technical Documentation

# Collision.subscriber.hpp
```cpp
#pragma once

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/Type.component.hpp"
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
                    std::cout << "YOU LOSE here" << std::endl;
                    data.movingEntity->removeAllComponents();
                    return;
                }
                if (data.movingEntity->has<BaseBulletComponent>()) {
                    if (data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                        data.collidingEntity->has<PlayerComponent>()) {
                        std::cout << "YOU LOSE here" << std::endl;
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
#include "Engine/Components/Position.component.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"

namespace Rtype::Subscriber
{
    class ShootPlayerPressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            ShootPlayerPressedSubscriber()           = default;
            ~ShootPlayerPressedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyPressedEvent &data) override
            {
                using namespace Engine::Components;

                if (data.keyEvent.code != sf::Keyboard::Space) return;
                Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                    Engine::EngineClass::getEngine().world().getSystems()["MovePlayer"].get());
                Engine::System::Bullets *bulletsSystem = dynamic_cast<Engine::System::Bullets *>(
                    Engine::EngineClass::getEngine().world().getSystems()["BulletsSystem"].get());
                ECS::Entity *player =
                    Engine::EngineClass::getEngine().world().getEntityWithComponents<PlayerComponent>();
                if (!player || !movePlayerSystem) return;

                ECS::ComponentHandle<Engine::Components::PositionComponent> pos =
                    player->getComponent<Engine::Components::PositionComponent>();
                bulletsSystem->spawnBullet(false, static_cast<float>(pos->x), static_cast<float>(pos->y), {1000, 0},
                                           200);
            }
    };

    class ShootPlayerReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
    {
        public:
            ShootPlayerReleasedSubscriber()           = default;
            ~ShootPlayerReleasedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyReleasedEvent &data) override
            {
                using namespace Engine::Components;

                if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                      data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                    return;
            }
    };
} // namespace Rtype::Subscriber
```
### **ShootPlayerPressedSubscriber Class:**

- **Purpose**: Subscribes to key-pressed events for player shooting.
- **Inherits From**: **`ECS::EventSubscriber<KeyPressedEvent>`**.
- **Constructor and Destructor**: Default constructor and destructor definitions.
- **Methods**:
    - **`receiveEvent`**: Overrides the base class method to handle key-pressed events.
        - Checks if the received key event corresponds to the spacebar (sf::Keyboard::Space).
        - Accesses the **`MovePlayer`** and **`Bullets`** systems and the player entity.
        - Retrieves the player's position component and instructs the **`Bullets`** system to spawn a bullet in the appropriate direction.

### **ShootPlayerReleasedSubscriber Class:**

- **Purpose**: Subscribes to key-released events for player shooting.
- **Inherits From**: **`ECS::EventSubscriber<KeyReleasedEvent>`**.
- **Constructor and Destructor**: Default constructor and destructor definitions.
- **Methods**:
    - **`receiveEvent`**: Overrides the base class method to handle key-released events.
        - Checks if the released key event corresponds to movement keys (W, A, S, D) but currently commented out and not utilized.