# R-Type/Components Technical Documentation

# BaseBullet.component.hpp
```cpp
#pragma once

#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct BaseBulletComponent : public ECS::BaseComponent {
        public:
            explicit BaseBulletComponent(bool fromEnemy) : fromEnemy(fromEnemy) {}
            ~BaseBulletComponent() override = default;

            bool fromEnemy;

        private:
    };
} // namespace Engine::Components
```
This component structure serves as a marker or identifier for bullets within the game. It contains information about the bullet's origin, specifically whether it's fired from an enemy or not. This distinction might be crucial for game mechanics or systems that handle bullet behavior, targeting, or collision detection based on their source.

**BaseBulletComponent Structure:**

**Constructor:**

- **`explicit BaseBulletComponent(bool fromEnemy)`**: Constructor initializing the **`BaseBulletComponent`** with a boolean parameter **`fromEnemy`**, indicating whether the bullet is from an enemy.

**Attributes:**

- **`bool fromEnemy`**: Indicates whether the bullet originates from an enemy (**`true`**) or not (**`false`**).

# Enemy.component.hpp
```cpp
#pragma once

#include <string>

#include "ECS/Components.hpp"
#include "R-Type/Systems/Enemy.system.hpp"

namespace Engine::Components
{
    struct EnemyComponent : ECS::BaseComponent {
        public:
            EnemyComponent(int health, EnemyData::EnemyType enemyType) : health(health), enemyType(enemyType) {}
            int                  health;
            EnemyData::EnemyType enemyType;
    };
} // namespace Engine::Components
```
This component structure serves to define essential characteristics of an enemy within the game. It holds data related to an enemy entity, such as its health points and type. This information is crucial for various systems or mechanics that interact with enemies, such as AI behavior, collision detection, or rendering specific enemy types differently.

**EnemyComponent Structure:**

**Constructor:**

- **`EnemyComponent(int health, EnemyData::EnemyType enemyType)`**: Constructor initializing the **`EnemyComponent`** with an integer parameter **`health`** representing the enemy's health and an **`EnemyData::EnemyType`** parameter **`enemyType`** specifying the type of the enemy.

**Attributes:**

- **`int health`**: Represents the health points of the enemy.
- **`EnemyData::EnemyType enemyType`**: Indicates the type of the enemy using the **`EnemyData::EnemyType`** enumeration from the **`R-Type/Systems/Enemy.system.hpp`** file.

# EnemyAttack.component.hpp
```cpp
#pragma once

#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct EnemyAttackComponent : public ECS::BaseComponent {
        public:
            EnemyAttackComponent(size_t attackRate, size_t bulletType, sf::Vector2f bulletDestination,
                                 size_t bulletDuration)
                : lastAttack(0), attackRate(attackRate), bulletType(bulletType), bulletDestination(bulletDestination),
                  bulletDuration(bulletDuration)
            {
            }

            ~EnemyAttackComponent() override = default;

            // last millisecond from epoch.
            size_t lastAttack;
            size_t attackRate;
            size_t bulletType;

            // these are the values to be passed to a MovingComponent.
            sf::Vector2f bulletDestination;
            size_t       bulletDuration;

        private:
    };
} // namespace Engine::Components
```
This component encapsulates data pertinent to an enemy's attack behavior. It holds information about the attack rate, bullet type, destination, and duration for the bullets. It likely interfaces with systems responsible for controlling enemy actions, such as firing bullets, managing their movement, and determining their behavior after being spawned.

**EnemyAttackComponent Structure:**

**Constructor:**

- **`EnemyAttackComponent(size_t attackRate, size_t bulletType, sf::Vector2f bulletDestination, size_t bulletDuration)`**: Constructor initializing the **`EnemyAttackComponent`** with parameters specifying the attack rate, bullet type, destination, and duration.

**Attributes:**

- **`size_t lastAttack`**: Records the last millisecond from the epoch representing the time of the last attack.
- **`size_t attackRate`**: Determines the rate of attack, possibly representing the cooldown period between attacks.
- **`size_t bulletType`**: Indicates the type of bullet to be used for the attack.
- **`sf::Vector2f bulletDestination`**: Specifies the destination (position) for the bullet upon its launch.
- **`size_t bulletDuration`**: Represents the duration of the bullet's existence or lifetime.

# EnemyMovements.component.hpp
```cpp
#pragma once

#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct EnemyMovementsComponent : public ECS::BaseComponent {
        public:
            EnemyMovementsComponent(std::vector<std::pair<size_t, sf::Vector2f>> movementsQueueLoop)
                : movementsQueueLoop(movementsQueueLoop), currentMove(0)
            {
            }

            ~EnemyMovementsComponent() override = default;

            std::vector<std::pair<size_t, sf::Vector2f>> movementsQueueLoop;
            size_t                                       currentMove;

        private:
    };
} // namespace Engine::Components
```
This component is responsible for managing the movement sequence of an enemy entity. It stores a sequence of movements represented by pairs of size_t and sf::Vector2f, presumably indicating movement details and destinations. The currentMove attribute manages the progress through the movement queue, possibly cycling through movements in a loop to define the enemy's pattern of motion within the game or application.

**EnemyMovementsComponent Structure:**

**Constructor:**

- **`EnemyMovementsComponent(std::vector<std::pair<size_t, sf::Vector2f>> movementsQueueLoop)`**: Constructor initializing the **`EnemyMovementsComponent`** with a queue of movement pairs and setting the current move to the initial position.

**Attributes:**

- **`std::vector<std::pair<size_t, sf::Vector2f>> movementsQueueLoop`**: Holds a queue of pairs representing movements. Each pair contains a size_t value (possibly indicating duration or type of movement) and an sf::Vector2f representing the movement destination or parameters.
- **`size_t currentMove`**: Tracks the index of the current movement within the movement queue.

# EnemyQueue.component.hpp
```cpp
#pragma once

#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct EnemyQueueComponent : public ECS::BaseComponent {
        public:
            EnemyQueueComponent() {}
            EnemyQueueComponent(
                std::vector<
                    std::pair<bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t(float, bool)>>>>
                    enemyQueueFactories)
                : enemyQueueFactories(enemyQueueFactories)
            {
            }

            ~EnemyQueueComponent() override = default;

            std::vector<std::pair<bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t(float, bool)>>>>
                enemyQueueFactories;

        private:
    };
} // namespace Engine::Components
```
This component manages a queue of enemy spawn data, including details such as spawn positions, attack states, and specific behaviors. The **`enemyQueueFactories`** attribute holds a collection of pairs that encapsulate information required to spawn enemies at specific game progress points and define their characteristics or behavior through the provided function.

**EnemyQueueComponent Structure:**

**Constructors:**

- **`EnemyQueueComponent()`**: Default constructor.
- **`EnemyQueueComponent(std::vector<std::pair<bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t(float, bool)>>>> enemyQueueFactories)`**: Constructor initializing the **`EnemyQueueComponent`** with a vector of pairs, each containing a boolean flag and a pair of complex data representing enemy spawning data along with a function.

**Attributes:**

- **`std::vector<std::pair<bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t(float, bool)>>>> enemyQueueFactories`**: Holds a vector of pairs, each containing:
    - A boolean indicating whether the enemy has spawned or not (defaulting to true).
    - A nested pair with complex data regarding the enemy to spawn. This data consists of:
        - A tuple containing:
            - A size_t value representing the x-coordinate where the map's progress should trigger enemy spawning.
            - A float value indicating the y-position.
            - A boolean flag ('isAttacking') determining if the enemy is in an attacking state.
        - A function that takes two floats and a boolean as parameters and returns a size_t value. This function seems to define or control enemy behavior or attributes based on given parameters.

# Missile.component.hpp
```cpp
#pragma once

#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct MissileComponent : public ECS::BaseComponent {
        public:
            MissileComponent() {}

            ~MissileComponent() override = default;

        private:
    };
} // namespace Engine::Components
```
The **`MissileComponent`** serve as a base component for missile entities but doesn't currently define any specific attributes or functionality beyond its default constructor and destructor.

**MissileComponent Structure:**

**Constructors:**

- **`MissileComponent()`**: Default constructor.

# Player.component.hpp

```cpp
#pragma once

#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct PlayerComponent : public ECS::BaseComponent {
        public:
            PlayerComponent(){};

            ~PlayerComponent() override = default;

        private:
    };
} // namespace Engine::Components
```

The **`PlayerComponent`** struct doesn't currently define any specific attributes or functionalities beyond its default constructor and destructor.

**PlayerComponent Structure:**

**Constructors:**

- **`PlayerComponent()`**: Default constructor.

**Attributes:**

- No specific attributes are explicitly defined within the structure.
