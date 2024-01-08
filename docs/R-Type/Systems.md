# R-Type/Systems Technical Documentation

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

            void spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time);
            void spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time,
                             float rotation);

        private:
    };
} // namespace Engine::System
```
### **`Bullets` Class:**
-  **Purpose:** Manages the spawning and animation of bullets in the game.
- **Inherits From**: **`ECS::BaseSystem`**.
- **Constructor and Destructor**:
    - **`Bullets(ECS::World &world)`**: Constructor that takes a reference to the ECS world.
    - **`Bullets(ECS::World &world, ECS::id_t ids...)`**: Constructor that takes a reference to the ECS world and a variable number of entity IDs for system configuration.
    - **`~Bullets() override = default;`**: Default destructor.
- **Methods**:
    - **`configure(ECS::World &world) override`**: Overrides the base class method for system configuration.
    - **`unconfigure() override`**: Overrides the base class method for system unconfiguration.
    - **`tick() override`**: Overrides the base class method to define the system's behavior on each tick.
    - **`spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time)`**: Spawns a bullet with the specified attributes.
    - **`spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time, float rotation)`**: Spawns a rotated bullet with the specified attributes.

# Enemy.system.hpp
```cpp
#pragma once

#include <utility>

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "SFML/System/Clock.hpp"
#include "Components/Collision.component.hpp"

namespace EnemyData
{
    enum class EnemyType {
        Weak,
        Normal,
        Strong
    };

    struct EnemyAttributes {
            std::string spritePath;
            int         health;

            EnemyAttributes(std::string sprite, int hp) : spritePath(std::move(sprite)), health(hp) {}
    };

    const std::unordered_map<EnemyType, EnemyAttributes> enemyTypeAttributes = {
        {EnemyType::Weak, EnemyAttributes("./assets/klaed/Klaed-Scout-Base.png", 50)},
        {EnemyType::Normal, EnemyAttributes("./assets/klaed/Klaed-Battlecruiser-Base.png", 100)},
        {EnemyType::Strong, EnemyAttributes("./assets/klaed/Klaed-Dreadnought-Base.png", 150)}};


} // namespace EnemyData
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

            size_t               spawnEnemy(float posx, float posy);
            bool                 shouldSpawnEnemy();
            EnemyData::EnemyType getRandomEnemyType();

        private:
            sf::Clock _clock;
    };
} // namespace Engine::System
```
### **`EnemySystem` Class:**

- **Purpose**: Manages enemy entities in the game, including their spawning, movement, and attacks.
- **Inherits From**: **`ECS::BaseSystem`**.
- **Includes**:
    - **`SFML/System/Clock.hpp`**: Used for time-related functionalities.
- **Enums and Structs**:
    - **`EnemyData::EnemyType`**: Enum defining different types of enemies (**`Weak`**, **`Normal`**, **`Strong`**).
    - **`EnemyData::EnemyAttributes`**: Struct holding attributes of enemies, such as sprite path and health.
    - **`EnemyData::enemyTypeAttributes`**: Map containing attributes for different enemy types.
- **Constants**:
    - **`ENEMY_SPAWN_RATE`**: Preprocessor definition setting the spawn rate for enemies to **`500`**.
- **Constructor and Destructor**:
    - **`EnemySystem(ECS::World &world)`**: Constructor taking a reference to the ECS world, initializes the system's clock.
    - **`EnemySystem(ECS::World &world, ECS::id_t ids...)`**: Constructor taking a reference to the ECS world and a variable number of entity IDs for system configuration, initializes the system's clock.
    - **`~EnemySystem() override = default;`**: Default destructor.
- **Methods**:
    - **`configure(ECS::World &world) override`**: Overrides the base class method for system configuration.
    - **`unconfigure() override`**: Overrides the base class method for system unconfiguration.
    - **`tick() override`**: Overrides the base class method to define the system's behavior on each tick.
    - **`tryChangeEnemiesMovement()`**: Attempts to modify enemy movements.
    - **`trySpawnEnemies()`**: Attempts to spawn enemies.
    - **`tryMakeEnemyAttack()`**: Attempts to make enemies attack.
    - **`spawnEnemy(float posx, float posy)`**: Deprecated method for spawning an enemy at a specific position.
    - **`shouldSpawnEnemy()`**: Checks if an enemy should be spawned based on the spawn rate.
    - **`getRandomEnemyType()`**: Retrieves a random enemy type for spawning.
- **Private Member**:
    - **`_clock`**: **`sf::Clock`** object used to manage timing within the system.

This system encapsulates enemy-related logic, handling their behavior and spawn mechanics within the game world.

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