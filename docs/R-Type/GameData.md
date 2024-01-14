# R-Type/GameData Technical Documentation

# EnemyData.hpp

```cpp
#pragma once

#include <string>
#include <unordered_map>

namespace EnemyData
{
    enum class EnemyType {
        Weak,
        Medium,
        Strong
    };

    struct EnemyAttributes {
            std::string spritePath;
            int         health;

            EnemyAttributes(std::string sprite, int hp) : spritePath(std::move(sprite)), health(hp) {}
    };

    const std::unordered_map<EnemyType, EnemyAttributes> enemyTypeAttributes = {
        {EnemyType::Weak, EnemyAttributes("./assets/klaed/Klaed-Scout-Base.png", 50)},
        {EnemyType::Medium, EnemyAttributes("./assets/klaed/Klaed-Battlecruiser-Base.png", 100)},
        {EnemyType::Strong, EnemyAttributes("./assets/klaed/Klaed-Dreadnought-Base.png", 150)}};

} // namespace EnemyData
```

### **`EnemyData` Namespace:**

1. **Purpose:**
    - Contains data related to different types of enemies in the game.
2. **Included Headers:**
    - **`<string>`**
    - **`<unordered_map>`**
3. **Namespace:**
    - **`EnemyData`**
4. **Enumerations:**
    - **`EnemyType`**:
        - Enumerates the different types of enemies, such as Weak, Medium, and Strong.
5. **Structures:**
    - **`EnemyAttributes`**:
        - Contains attributes associated with an enemy type.
        - Members:
            - **`spritePath`** (type: **`std::string`**): Path to the sprite image for the enemy.
            - **`health`** (type: **`int`**): Health points of the enemy.
6. **Constants:**
    - **`enemyTypeAttributes`**:
        - An unordered map mapping each **`EnemyType`** to its corresponding **`EnemyAttributes`**.
        - Provides predefined attributes for different enemy types.
        - Includes paths to sprite images and initial health points.