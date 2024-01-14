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

# Booster.component.hpp
```cpp
#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "ECS/Components.hpp"

namespace Rtype::Components
{
    struct BoosterComponent : ECS::BaseComponent {
        public:
            BoosterComponent() : duration_seconds(0){};
            BoosterComponent(int duration) : duration_seconds(duration){};
            ~BoosterComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&duration_seconds), sizeof(duration_seconds));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                BoosterComponent *boosterComponent;
                if (component == nullptr) {
                    boosterComponent = new BoosterComponent(0);
                } else {
                    boosterComponent = dynamic_cast<BoosterComponent *>(component);
                    if (boosterComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&boosterComponent->duration_seconds),
                         sizeof(boosterComponent->duration_seconds));

                return boosterComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::BoosterComponent;
            }

            int duration_seconds;
    };

    struct isBoosterComponent : ECS::BaseComponent {
        public:
            isBoosterComponent()           = default;
            ~isBoosterComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                isBoosterComponent *isBoosterComponent;
                if (component == nullptr) {
                    isBoosterComponent = new struct isBoosterComponent();
                } else {
                    isBoosterComponent = dynamic_cast<struct isBoosterComponent *>(component);
                    if (isBoosterComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                return isBoosterComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::isBoosterComponent;
            }
    };

} // namespace Rtype::Components
```

### **`BoosterComponent` and `isBoosterComponent` Classes:**

1. **`BoosterComponent` Class:**
    - **Purpose**: Represents a component that can be attached to entities in an ECS-based game to provide a boost effect for a specified duration.
    - **Inherits From**: **`ECS::BaseComponent`**
    - **Constructors**:
        - Default Constructor: Initializes the **`BoosterComponent`** with a zero-duration boost.
        - Constructor with Duration: Initializes the **`BoosterComponent`** with a specified duration for the boost effect.
    - **Member Functions**:
        - **`serialize`**: Serializes the component's data to a vector of characters.
        - **`deserialize`**: Deserializes the component's data from a vector of characters.
        - **`getType`**: Returns the type of the component.
2. **`isBoosterComponent` Class:**
    - **Purpose**: Represents a marker component that can be attached to entities in an ECS-based game to indicate the presence of a booster effect.
    - **Inherits From**: **`ECS::BaseComponent`**
    - **Constructors**:
        - Default Constructor: Initializes the **`isBoosterComponent`**.
    - **Member Functions**:
        - **`serialize`**: Serializes the component's data to a vector of characters.
        - **`deserialize`**: Deserializes the component's data from a vector of characters.
        - **`getType`**: Returns the type of the component.

# BoosterActive.component.hpp
```cpp
#pragma once

#include <sstream>
#include <vector>

#include "ECS/Components.hpp"
#include "SFML/System/Clock.hpp"

namespace Rtype::Components
{
    struct BoosterActiveComponent : ECS::BaseComponent {
        public:
            BoosterActiveComponent() : duration(0), clock({}) {}
            BoosterActiveComponent(int duration) : duration(duration), clock({}) {}
            ~BoosterActiveComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&duration), sizeof(duration));
                oss.write(reinterpret_cast<const char *>(&hitpoints), sizeof(hitpoints));
                oss.write(reinterpret_cast<const char *>(&clock), sizeof(clock));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                BoosterActiveComponent *boosterActiveComponent;
                if (component == nullptr) {
                    boosterActiveComponent = new BoosterActiveComponent(0);
                } else {
                    boosterActiveComponent = dynamic_cast<BoosterActiveComponent *>(component);
                    if (boosterActiveComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&boosterActiveComponent->duration),
                         sizeof(boosterActiveComponent->duration));
                iss.read(reinterpret_cast<char *>(&boosterActiveComponent->hitpoints),
                         sizeof(boosterActiveComponent->hitpoints));
                iss.read(reinterpret_cast<char *>(&boosterActiveComponent->clock),
                         sizeof(boosterActiveComponent->clock));

                return boosterActiveComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::BoosterActiveComponent;
            }

            int       duration;
            int       hitpoints = 3;
            sf::Clock clock;
    };

} // namespace Rtype::Components
```

### **`BoosterActiveComponent` Class:**

1. **`BoosterActiveComponent` Class:**
    - **Purpose**: Represents a component that indicates the active state of a booster effect. It includes information about the remaining duration, hitpoints, and a clock for time tracking.
    - **Inherits From**: **`ECS::BaseComponent`**
    - **Constructors**:
        - Default Constructor: Initializes the **`BoosterActiveComponent`** with a zero-duration boost, 3 hitpoints, and a clock.
        - Constructor with Duration: Initializes the **`BoosterActiveComponent`** with a specified duration for the boost effect, 3 hitpoints, and a clock.
    - **Member Functions**:
        - **`serialize`**: Serializes the component's data to a vector of characters.
        - **`deserialize`**: Deserializes the component's data from a vector of characters.
        - **`getType`**: Returns the type of the component.

# DeathAnimation.component.hpp
```cpp
#pragma once

#include <string>

#include "Engine/Components/Animation.component.hpp"

namespace Engine::Components
{

    class DeathAnimationComponent : public AnimationComponent
    {
        public:
            DeathAnimationComponent(std::string animationPath, int x, int y, int width, int height, int tx, int ty,
                                    int animationSpeed, int frameCount)
                : AnimationComponent(x, y, width, height, tx, ty, animationSpeed, frameCount),
                  animationPath(animationPath)
            {
            }

            ~DeathAnimationComponent() override = default;

            std::string animationPath;
    };
} // namespace Engine::Components
```
### **`DeathAnimationComponent` Class:**

1. **`DeathAnimationComponent` Class:**
    - **Purpose:** Represents a component for death animations. It extends the **`AnimationComponent`** class, providing specific parameters for death animations.
    - **Inherits From:** **`AnimationComponent`**
    - **Constructors:**
        - Constructor with Parameters:
            - Initializes the **`DeathAnimationComponent`** with the provided animation path, offset from the top-left corner (x, y), width, height, tile size (tx, ty), animation speed in milliseconds, and frame count.
    - **Member Variables:**
        - **`animationPath`**: A string representing the path to the animation sprite for death.
    - **Destructor:**
        - Default destructor.
    - **Inherited Member Functions:**
        - Inherited from **`AnimationComponent`**.


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
#include <sstream>
#include <tuple>
#include <vector>

#include "ECS/Components.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct EnemyQueueComponent : public ECS::BaseComponent {
        public:
            EnemyQueueComponent() = default;

            explicit EnemyQueueComponent(
                std::vector<std::pair<
                    bool,
                    std::pair<std::tuple<size_t, float, bool, std::vector<std::pair<size_t, sf::Vector2f>>>, size_t>>>
                    newEnemyQueueFactories)
                : newEnemyQueueFactories(newEnemyQueueFactories)
            {
            }

            ~EnemyQueueComponent() override = default;

            // Sérialisation pour newEnemyQueueFactories
            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                size_t             size = newEnemyQueueFactories.size();
                oss.write(reinterpret_cast<const char *>(&size), sizeof(size));

                for (const auto &item : newEnemyQueueFactories) {
                    // Sérialiser le bool
                    bool hasSpawned = item.first;
                    oss.write(reinterpret_cast<const char *>(&hasSpawned), sizeof(hasSpawned));

                    // Sérialiser les données du tuple
                    auto &[x, y, isAttacking, positions] = item.second.first;
                    oss.write(reinterpret_cast<const char *>(&x), sizeof(x));
                    oss.write(reinterpret_cast<const char *>(&y), sizeof(y));
                    oss.write(reinterpret_cast<const char *>(&isAttacking), sizeof(isAttacking));

                    size_t positionsSize = positions.size();
                    oss.write(reinterpret_cast<const char *>(&positionsSize), sizeof(positionsSize));
                    for (const auto &pos : positions) {
                        size_t       posId    = pos.first;
                        sf::Vector2f posValue = pos.second;
                        oss.write(reinterpret_cast<const char *>(&posId), sizeof(posId));
                        oss.write(reinterpret_cast<const char *>(&posValue), sizeof(posValue));
                    }

                    // Sérialiser le size_t (factoryId)
                    size_t factoryId = item.second.second;
                    oss.write(reinterpret_cast<const char *>(&factoryId), sizeof(factoryId));
                }

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) override
            {
                EnemyQueueComponent *enemyQueueComponent;
                if (component == nullptr) {
                    enemyQueueComponent = new EnemyQueueComponent();
                } else {
                    enemyQueueComponent = dynamic_cast<EnemyQueueComponent *>(component);
                    if (enemyQueueComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                size_t size;
                iss.read(reinterpret_cast<char *>(&size), sizeof(size));

                newEnemyQueueFactories.clear();
                for (size_t i = 0; i < size; ++i) {
                    bool hasSpawned;
                    iss.read(reinterpret_cast<char *>(&hasSpawned), sizeof(hasSpawned));

                    size_t x;
                    float  y;
                    bool   isAttacking;
                    iss.read(reinterpret_cast<char *>(&x), sizeof(x));
                    iss.read(reinterpret_cast<char *>(&y), sizeof(y));
                    iss.read(reinterpret_cast<char *>(&isAttacking), sizeof(isAttacking));

                    size_t positionsSize;
                    iss.read(reinterpret_cast<char *>(&positionsSize), sizeof(positionsSize));
                    std::vector<std::pair<size_t, sf::Vector2f>> positions;
                    for (size_t j = 0; j < positionsSize; ++j) {
                        size_t       posId;
                        sf::Vector2f posValue;
                        iss.read(reinterpret_cast<char *>(&posId), sizeof(posId));
                        iss.read(reinterpret_cast<char *>(&posValue), sizeof(posValue));
                        positions.emplace_back(posId, posValue);
                    }

                    size_t factoryId;
                    iss.read(reinterpret_cast<char *>(&factoryId), sizeof(factoryId));

                    newEnemyQueueFactories.emplace_back(
                        hasSpawned, std::make_pair(std::make_tuple(x, y, isAttacking, positions), factoryId));
                }
                return enemyQueueComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::EnemyQueueComponent;
            }

            std::vector<std::pair<
                bool, std::pair<std::tuple<size_t, float, bool, std::vector<std::pair<size_t, sf::Vector2f>>>, size_t>>>
                newEnemyQueueFactories = {};

        private:
    };
} // namespace Engine::Components
```
### **`EnemyQueueComponent` Class:**

1. **Purpose:**
    - Represents a component for managing a queue of enemy factories, indicating whether each enemy has spawned or not.
2. **Inherits From:**
    - **`ECS::BaseComponent`**
3. **Constructors:**
    - Default Constructor:
        - Initializes an empty **`EnemyQueueComponent`**.
    - Constructor with Parameters:
        - Initializes the **`EnemyQueueComponent`** with a vector of enemy factory data.
4. **Member Variables:**
    - **`newEnemyQueueFactories`**:
        - A vector containing pairs of a boolean indicating whether the enemy has spawned and a pair of data about the enemy to spawn (x, y, isAttacking, positions, factoryId).
5. **Member Functions:**
    - **`serialize`**:
        - Serializes the **`newEnemyQueueFactories`** data into a binary string.
    - **`deserialize`**:
        - Deserializes the binary string data into the **`newEnemyQueueFactories`** vector.
    - **`getType`**:
        - Returns the component type as **`EnemyQueueComponent`**.
6. **Destructor:**
    - Default destructor.


# Missile.component.hpp
```cpp
#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct MissileComponent : public ECS::BaseComponent {
        public:
            MissileComponent() = default;

            ~MissileComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                MissileComponent *missileComponent;
                if (component == nullptr) {
                    missileComponent = new MissileComponent();
                } else {
                    missileComponent = dynamic_cast<MissileComponent *>(component);
                    if (missileComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                return missileComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::MissileComponent;
            }

        private:
    };
} // namespace Engine::Components
```

### **`MissileComponent` Class:**

1. **Purpose:**
    - Represents a component indicating the presence of a missile entity.
2. **Inherits From:**
    - **`ECS::BaseComponent`**
3. **Constructors:**
    - Default Constructor:
        - Initializes an empty **`MissileComponent`**.
4. **Member Functions:**
    - **`serialize`**:
        - Serializes the **`MissileComponent`** data into a binary string.
    - **`deserialize`**:
        - Deserializes the binary string data into a new **`MissileComponent`**.
    - **`getType`**:
        - Returns the component type as **`MissileComponent`**.
5. **Destructor:**
    - Default destructor.

# Player.component.hpp

```cpp
#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct PlayerComponent : public ECS::BaseComponent {
        public:
            PlayerComponent() : playerNb(0){};

            PlayerComponent(int playerNb) : playerNb(playerNb){};

            ~PlayerComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);

                oss.write(reinterpret_cast<const char *>(&playerNb), sizeof(playerNb));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(const std::vector<char> vec, ECS::BaseComponent *component) final
            {
                PlayerComponent *playerComponent;
                if (component == nullptr) {
                    playerComponent = new PlayerComponent();
                } else {
                    playerComponent = dynamic_cast<PlayerComponent *>(component);
                    if (playerComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                iss.read(reinterpret_cast<char *>(&playerComponent->playerNb), sizeof(playerComponent->playerNb));

                return playerComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::PlayerComponent;
            }

            int playerNb;
    };
} // namespace Engine::Components
```

### **`PlayerComponent` Class:**

1. **Purpose:**
    - Represents a component indicating the player number associated with an entity.
2. **Inherits From:**
    - **`ECS::BaseComponent`**
3. **Constructors:**
    - Default Constructor:
        - Initializes a **`PlayerComponent`** with a default player number of 0.
    - Parameterized Constructor:
        - Initializes a **`PlayerComponent`** with a specified player number.
4. **Member Functions:**
    - **`serialize`**:
        - Serializes the **`PlayerComponent`** data into a binary string.
    - **`deserialize`**:
        - Deserializes the binary string data into a new **`PlayerComponent`**.
    - **`getType`**:
        - Returns the component type as **`PlayerComponent`**.
5. **Destructor:**
    - Default destructor.

# WeaponType.component.hpp
```cpp
#pragma once

#include <array>
#include <vector>

#include "ECS/Components.hpp"

namespace Rtype::Components
{
    enum WeaponType {
        BASIC,
        BIG
    };

    static const std::array<bool, 2> canCharge     = {false, true};
    static const std::array<int, 2>  chargeTimeLst = {0, 2000};
    static const std::array<int, 2>  damageLst     = {1, 2};
    static const std::array<int, 2>  durationLst   = {0, 5000};
    static const std::array<int, 2>  rateOfFireLst = {200, 1500};

    struct WeaponTypeComponent : ECS::BaseComponent {

            WeaponTypeComponent()
                : type(BASIC), isChargeable(canCharge[BASIC]), chargeTime(chargeTimeLst[BASIC]),
                  damage(damageLst[BASIC]), duration(durationLst[BASIC]), rateOfFire(rateOfFireLst[BASIC])
            {
            }

            explicit WeaponTypeComponent(WeaponType type)
                : type(type), isChargeable(canCharge[type]), chargeTime(chargeTimeLst[type]), damage(damageLst[type]),
                  duration(durationLst[type]), rateOfFire(rateOfFireLst[type])
            {
            }
            ~WeaponTypeComponent() override = default;

            void reset(WeaponType type)
            {
                this->type         = type;
                this->isChargeable = canCharge[type];
                this->chargeTime   = chargeTimeLst[type];
                this->damage       = damageLst[type];
                this->duration     = durationLst[type];
                this->rateOfFire   = rateOfFireLst[type];
            }

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&type), sizeof(type));
                oss.write(reinterpret_cast<const char *>(&isChargeable), sizeof(isChargeable));
                oss.write(reinterpret_cast<const char *>(&chargeTime), sizeof(chargeTime));
                oss.write(reinterpret_cast<const char *>(&damage), sizeof(damage));
                oss.write(reinterpret_cast<const char *>(&duration), sizeof(duration));
                oss.write(reinterpret_cast<const char *>(&rateOfFire), sizeof(rateOfFire));

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                WeaponTypeComponent *weaponTypeComponent;
                if (component == nullptr) {
                    weaponTypeComponent = new WeaponTypeComponent();
                } else {
                    weaponTypeComponent = dynamic_cast<WeaponTypeComponent *>(component);
                    if (weaponTypeComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->type), sizeof(weaponTypeComponent->type));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->isChargeable),
                         sizeof(weaponTypeComponent->isChargeable));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->chargeTime),
                         sizeof(weaponTypeComponent->chargeTime));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->damage), sizeof(weaponTypeComponent->damage));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->duration),
                         sizeof(weaponTypeComponent->duration));
                iss.read(reinterpret_cast<char *>(&weaponTypeComponent->rateOfFire),
                         sizeof(weaponTypeComponent->rateOfFire));

                return weaponTypeComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::WeaponTypeComponent;
            }

            WeaponType type;
            bool       isChargeable = false;
            int        chargeTime   = 0;
            int        damage       = 0;
            int        duration     = 0;
            int        rateOfFire   = 0;
    };
} // namespace Rtype::Components
```

### **`WeaponTypeComponent` Class:**

1. **Purpose:**
    - Represents a component specifying the weapon type associated with an entity.
2. **Inherits From:**
    - **`ECS::BaseComponent`**
3. **Enumerations:**
    - **`WeaponType`**:
        - Enumerates different weapon types (**`BASIC`**, **`BIG`**).
4. **Static Constants:**
    - **`canCharge`**:
        - A static array indicating whether each weapon type can be charged.
    - **`chargeTimeLst`**:
        - A static array specifying the charge time for each weapon type.
    - **`damageLst`**:
        - A static array indicating the damage for each weapon type.
    - **`durationLst`**:
        - A static array specifying the duration for each weapon type.
    - **`rateOfFireLst`**:
        - A static array indicating the rate of fire for each weapon type.
5. **Constructors:**
    - Default Constructor:
        - Initializes a **`WeaponTypeComponent`** with default values for the **`BASIC`** weapon type.
    - Parameterized Constructor:
        - Initializes a **`WeaponTypeComponent`** with values corresponding to the specified weapon type.
6. **Member Functions:**
    - **`reset`**:
        - Resets the component's values based on the specified weapon type.
    - **`serialize`**:
        - Serializes the **`WeaponTypeComponent`** data into a binary string.
    - **`deserialize`**:
        - Deserializes the binary string data into a new **`WeaponTypeComponent`**.
    - **`getType`**:
        - Returns the component type as **`WeaponTypeComponent`**.

