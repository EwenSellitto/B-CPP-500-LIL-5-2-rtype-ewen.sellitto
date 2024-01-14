# R-Type/Events Technical Documentation

# EnnemyDeath.event.hpp

```cpp
#pragma once

#include "ECS/Entity.hpp"

namespace Rtype::Events
{
    struct EnnemyDeath {
        public:
            EnnemyDeath(ECS::Entity *enemy) : Enemy(enemy) {}
            ~EnnemyDeath() = default;

            ECS::Entity *Enemy;
    };
} // namespace Rtype::Events
```

### **`EnemyDeath` Event:**

1. **Purpose:**
    - Represents an event signaling the death of an enemy entity.
2. **Included Headers:**
    - **`"ECS/Entity.hpp"`**
3. **Class Structure:**
    - **Class Name:** **`EnnemyDeath`**
    - **Namespace:** **`Rtype::Events`**
4. **Constructor:**
    - Parameterized Constructor:
        - Accepts a pointer to the **`ECS::Entity`** representing the enemy that has died.
5. **Member Variables:**
    - **`Enemy`**:
        - Pointer to the **`ECS::Entity`** representing the dead enemy.