# R-Type/Systems Technical Documentation

# Booster.system.hpp
```cpp
#pragma once

#include "ECS/Entity.hpp"
#include "ECS/System.hpp"

namespace Rtype::System
{
    class BoosterSystem : public ECS::BaseSystem
    {
        public:
            BoosterSystem(ECS::World &world) : ECS::BaseSystem(world) {}
            BoosterSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~BoosterSystem() override = default;

            void configure([[maybe_unused]] ECS::World &world) override {}

            void unconfigure() override {}
            void tick() override;

            static void takeBooster(ECS::Entity *player, ECS::Entity *booster);
    };
} // namespace Rtype::System
```
### **`BoosterSystem` Class:**

1. **Purpose:**
    - Manages boosters within the game world.
2. **Inherits From:**
    - **`ECS::BaseSystem`**
3. **Constructors:**
    - Overloaded constructor(s) for initializing the system with the specified world and optional entity IDs.
4. **Destructor:**
    - Default destructor for the **`BoosterSystem`** class.
5. **Member Functions:**
    - **`configure`**:
        - Overrides the base class method for configuring the system. (Not utilized in this system)
    - **`unconfigure`**:
        - Overrides the base class method for unconfiguring the system. (Not utilized in this system)
    - **`tick`**:
        - Overrides the base class method and is called each frame.
        - Manages the logic related to boosters within the game world.
    - **`takeBooster`**:
        - Static function to handle the interaction between a player entity and a booster entity.
        - Takes two parameters: **`player`** (ECS::Entity pointer) and **`booster`** (ECS::Entity pointer).
        - Defines the logic for a player entity acquiring the effects of a booster entity.

# Bullets.system.hpp
```cpp
#pragma once

#include "ECS/System.hpp"
#include "ECS/Utilities.hpp"
#include "ECS/World.hpp"

enum class bulletType {
    Weak,
    Normal,
    Strong
};

namespace Engine::System
{
    class Bullets : public ECS::BaseSystem
    {
        public:
            Bullets(ECS::World &world) : ECS::BaseSystem(world) {}
            Bullets(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~Bullets() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time,
                             int dmg = 50);
            void spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time,
                             float rotation, int dmg = 50);
            void spawnBigBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time,
                                float rotation, int dmg = 50);

        private:
    };
} // namespace Engine::System
```

### **`Bullets` Class:**

1. **Purpose:**
    - Manages the spawning and behavior of bullets within the game.
2. **Inherits From:**
    - **`ECS::BaseSystem`**
3. **Constructors:**
    - **`Bullets(ECS::World &world)`**: Constructs the **`Bullets`** system with the specified world.
    - **`Bullets(ECS::World &world, ECS::id_t ids...)`**: Overloaded constructor allowing specification of entity IDs.
4. **Destructor:**
    - Default destructor for the **`Bullets`** class.
5. **Member Functions:**
    - **`configure()`**: Overrides the base class method for configuring the system. (Not utilized in this system)
    - **`unconfigure()`**: Overrides the base class method for unconfiguring the system. (Not utilized in this system)
    - **`tick()`**: Overrides the base class method; called each frame. Manages bullet behavior in the game world.
    - **`spawnBullet()`**: Spawns a bullet entity.
    - **`spawnRotatedBullet()`**: Spawns a rotated bullet entity.
    - **`spawnBigBullet()`**: Spawns a big bullet entity.

# DeathAnimation.system.hpp
```cpp
#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class DeathAnimationSystem : public ECS::BaseSystem
    {
        public:
            DeathAnimationSystem(ECS::World &world) : ECS::BaseSystem(world) {}
            DeathAnimationSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~DeathAnimationSystem() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;
    };
} // namespace Engine::System

```
### **`DeathAnimationSystem` Class:**

1. **Purpose:**
    - Manages the death animation system within the game.
2. **Inherits From:**
    - **`ECS::BaseSystem`**
3. **Constructors:**
    - **`DeathAnimationSystem(ECS::World &world)`**: Constructs the **`DeathAnimationSystem`** with the specified world.
    - **`DeathAnimationSystem(ECS::World &world, ECS::id_t ids...)`**: Overloaded constructor allowing specification of entity IDs.
4. **Destructor:**
    - Default destructor for the **`DeathAnimationSystem`** class.
5. **Member Functions:**
    - **`configure()`**: Overrides the base class method for configuring the system. (Not utilized in this system)
    - **`unconfigure()`**: Overrides the base class method for unconfiguring the system. (Not utilized in this system)
    - **`tick()`**: Overrides the base class method; called each frame. Manages death animation behavior in the game world.


# Enemy.system.hpp
```cpp
#pragma once

#include <chrono>

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "R-Type/gameData/EnemyData.hpp"
#include "SFML/System/Clock.hpp"

#ifndef ENEMY_SPAWN_RATE
#define ENEMY_SPAWN_RATE 500
#endif

namespace Engine::System
{
    class EnemySystem : public ECS::BaseSystem
    {
        public:
            EnemySystem(ECS::World &world) : ECS::BaseSystem(world), _clock()
            {
                _clock.restart();
            }
            EnemySystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids), _clock()
            {
                _clock.restart();
            }
            ~EnemySystem() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void tryChangeEnemiesMovement();
            void trySpawnEnemies();
            void tryMakeEnemyAttack();

            // this spawnEnemy is deprecated, a factory inside EnemyQueue is used instead;
            size_t               spawnEnemy(float posx, float posy);
            bool                 shouldSpawnEnemy();
            EnemyData::EnemyType getRandomEnemyType();

        private:
            sf::Clock _clock;
    };
} // namespace Engine::System
```

### **`EnemySystem` Class:**

1. **Purpose:**
    - Manages the enemy system within the game, handling enemy spawn rates, movement, and attacks.
2. **Inherits From:**
    - **`ECS::BaseSystem`**
3. **Constructors:**
    - **`EnemySystem(ECS::World &world)`**: Constructs the **`EnemySystem`** with the specified world and initializes the clock.
    - **`EnemySystem(ECS::World &world, ECS::id_t ids...)`**: Overloaded constructor allowing specification of entity IDs, also initializes the clock.
4. **Destructor:**
    - Default destructor for the **`EnemySystem`** class.
5. **Member Functions:**
    - **`configure(ECS::World &world)`**: Overrides the base class method for configuring the system.
    - **`unconfigure()`**: Overrides the base class method for unconfiguring the system.
    - **`tick()`**: Overrides the base class method; called each frame. Manages enemy-related behavior in the game world, such as movement, attacks, and spawning.
    - **`tryChangeEnemiesMovement()`**: Attempts to change the movement pattern of enemies.
    - **`trySpawnEnemies()`**: Attempts to spawn enemies based on the configured spawn rate.
    - **`tryMakeEnemyAttack()`**: Attempts to make enemies attack.
    - **`spawnEnemy(float posx, float posy)`**: Deprecated method to spawn enemies; a factory inside **`EnemyQueue`** is used instead.
    - **`shouldSpawnEnemy()`**: Checks if an enemy should be spawned based on the configured spawn rate.
    - **`getRandomEnemyType()`**: Returns a random enemy type for spawning.

# Health.system.hpp
```cpp
#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Rtype::Systems
{
    class HealthSystem : public ECS::BaseSystem
    {
        public:
            HealthSystem(ECS::World &world) : ECS::BaseSystem(world){};
            HealthSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~HealthSystem() override = default;

            void configure([[maybe_unused]] ECS::World &world) override {}
            void unconfigure() override {}

            void tick() override;
    };
} // namespace Rtype::Systems
```

### **`HealthSystem` Class:**

1. **Purpose:**
    - Manages the health system within the game, handling health-related aspects of entities.
2. **Inherits From:**
    - **`ECS::BaseSystem`**
3. **Constructors:**
    - **`HealthSystem(ECS::World &world)`**: Constructs the **`HealthSystem`** with the specified world.
    - **`HealthSystem(ECS::World &world, ECS::id_t ids...)`**: Overloaded constructor allowing specification of entity IDs.
4. **Destructor:**
    - Default destructor for the **`HealthSystem`** class.
5. **Member Functions:**
    - **`configure(ECS::World &world)`**: Overrides the base class method for configuring the system.
    - **`unconfigure()`**: Overrides the base class method for unconfiguring the system.
    - **`tick()`**: Overrides the base class method; called each frame. Manages health-related behaviors in the game world.

# MovePlayer.system.hpp
```cpp
#pragma once

#include <SFML/Window/Event.hpp>

#include "ECS/Entity.hpp"
#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class MovePlayer : public ECS::BaseSystem
    {
        public:
            explicit MovePlayer(ECS::World &world) : ECS::BaseSystem(world){};
            MovePlayer(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~MovePlayer() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void addMovePlayer(sf::Event::KeyEvent key);
            void stopMovePlayer(sf::Event::KeyEvent key);
    };
} // namespace Engine::System
```
### **`MovePlayer` Class:**

- **Purpose**: Manages the movement of the player entity in the game.
- **Inherits From**: **`ECS::BaseSystem`**.
- **Includes**:
    - **`SFML/Window/Event.hpp`**: For handling SFML window events.
- **Constructor and Destructor**:
    - **`MovePlayer(ECS::World &world)`**: Constructor taking a reference to the ECS world, initializing the system.
    - **`MovePlayer(ECS::World &world, ECS::id_t ids...)`**: Constructor taking a reference to the ECS world and a variable number of entity IDs for system configuration.
    - **`~MovePlayer() override = default;`**: Default destructor.
- **Methods**:
    - **`configure(ECS::World &world) override`**: Overrides the base class method for system configuration.
    - **`unconfigure() override`**: Overrides the base class method for system unconfiguration.
    - **`tick() override`**: Overrides the base class method to define the system's behavior on each tick.
    - **`addMovePlayer(sf::Event::KeyEvent key)`**: Adds a movement command based on the received key event.
    - **`stopMovePlayer(sf::Event::KeyEvent key)`**: Stops the player movement based on the received key event.

This system facilitates player movement by capturing input events and translating them into movement commands within the game world.