# Engine/Systems Technical Documentation

# Animation.system.hpp
```cpp
pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class AnimationSystem : public ECS::BaseSystem
    {
        public:
            AnimationSystem(ECS::World &world) : ECS::BaseSystem(world) {}
            AnimationSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~AnimationSystem() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;
    };
} // namespace Engine::System
```
This class define an **`AnimationSystem`** responsible for managing animations within an ECS (Entity-Component-System) architecture. It sets up methods for configuring, unconfiguring, and processing animation-related logic within the game or application. The system operates within the context of an ECS world, suggesting its role in handling animation-related entities and components within the broader game engine or system.

### **AnimationSystem Class:**

- **Inheritance:**
    - Inherits from **`ECS::BaseSystem`**.
- **Constructors:**
    - **`AnimationSystem(ECS::World &world)`**: Constructor initializing the **`AnimationSystem`** with a reference to an **`ECS::World`**.
    - **`AnimationSystem(ECS::World &world, ECS::id_t ids...)`**: Constructor allowing initialization with a world reference and variable **`ECS::id_t`** identifiers.
- **Destructor:**
    - **`~AnimationSystem() override`**: Default destructor for the **`AnimationSystem`** class.
- **Methods:**
    - **`void configure(ECS::World &world) override`**: Method to configure the system, taking a world reference as a parameter.
    - **`void unconfigure() override`**: Method to unconfigure or reset the system.
    - **`void tick() override`**: Method to execute the system logic during each iteration.

# Parallax.system.hpp
```cpp
#pragma once
#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class ParallaxSystem : public ECS::BaseSystem
    {
        public:
            ParallaxSystem(ECS::World &world) : ECS::BaseSystem(world) {}

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;
    };
} // namespace Engine::System
```
This class defines a **`ParallaxSystem`** responsible for managing the parallax effect within an ECS architecture. It's designed to handle the configuration, execution, and management of parallax behavior in the game or application's world context, hinting at its role in managing background layers' movement and rendering in the broader game engine or system.

**ParallaxSystem Class:**

**Inheritance:**

- Inherits from **`ECS::BaseSystem`**.

**Constructors:**

- **`ParallaxSystem(ECS::World &world)`**: Initializes the **`ParallaxSystem`** with a reference to an **`ECS::World`**.

**Methods:**

- **`void configure(ECS::World &world) override`**: Configures the system, taking a world reference as a parameter.
- **`void unconfigure() override`**: Handles unconfiguring or resetting the system.
- **`void tick() override`**: Executes the system's logic during each iteration.

# Physics.system.hpp
```cpp
#pragma once

#include <ctime>

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Moving.component.hpp"

namespace Engine::System
{
    class Physics : public ECS::BaseSystem
    {
        public:
            Physics(ECS::World &world) : ECS::BaseSystem(world){};
            Physics(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~Physics() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            // move functions
            void moveTime(ECS::Entity *entity, ECS::ComponentHandle<Components::MovingComponent> handle);

            // collision function
            void collide(ECS::Entity *entity, int x, int y);
    };
} // namespace Engine::System
```
This class encapsulates a **`Physics`** system, responsible for managing physics-related operations like entity movement based on time and collision handling. It integrates within an ECS framework, suggesting its role in governing the physics behaviors and interactions within the broader game or application system.

**Physics Class:**

**Inheritance:**

- Inherits from **`ECS::BaseSystem`**.

**Constructors:**

- **`Physics(ECS::World &world)`**: Initializes the **`Physics`** system with a reference to an **`ECS::World`**.

**Methods:**

- **`void configure(ECS::World &world) override`**: Configures the system, taking a world reference as a parameter.
- **`void unconfigure() override`**: Manages the unconfiguration or resetting of the system.
- **`void tick() override`**: Executes the system's logic during each iteration.

**Functionality:**

- **`void moveTime(ECS::Entity *entity, ECS::ComponentHandle<Components::MovingComponent> handle)`**: Handles moving entities based on time-related calculations.
- **`void collide(ECS::Entity *entity, int x, int y)`**: Manages collision detection and resolution for entities in the system.

# Renderer.system.hpp
```cpp
#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class Renderer : public ECS::BaseSystem
    {
        public:
            Renderer(ECS::World &world) : ECS::BaseSystem(world){};
            Renderer(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~Renderer() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;
    };
} // namespace Engine::System
```
This class defines a **`Renderer`** system aimed at managing rendering-related operations within the ECS framework. It's responsible for configuring, handling, and processing rendering logic within the broader context of a game engine or application system.

**Renderer Class:**

**Inheritance:**

- Inherits from **`ECS::BaseSystem`**.

**Constructors:**

- **`Renderer(ECS::World &world)`**: Initializes the **`Renderer`** system with a reference to an **`ECS::World`**.

**Methods:**

- **`void configure(ECS::World &world) override`**: Configures the system, accepting a world reference as a parameter.
- **`void unconfigure() override`**: Manages the unconfiguration or resetting of the system.
- **`void tick() override`**: Executes the system's logic during each iteration.

# UI.system.hpp
```cpp
#pragma once

#include "ECS/Components.hpp"
#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Renderable.component.hpp"

namespace Engine::System
{
    class UI : public ECS::BaseSystem
    {
        public:
            UI(ECS::World &world) : ECS::BaseSystem(world){};
            UI(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~UI() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

        private:
            void handleStartGame();
            void updateButtonState(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                                   ECS::ComponentHandle<Components::RenderableComponent> renderable,
                                   const sf::Vector2f                                   &worldPos);
            void resetButtonVisual(ECS::ComponentHandle<Components::RenderableComponent> renderable);
            void hoverEffect(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                             ECS::ComponentHandle<Components::RenderableComponent> renderable);
            void handleClick(ECS::ComponentHandle<Components::ButtonComponent>     buttonComp,
                             ECS::ComponentHandle<Components::RenderableComponent> renderable);
    };
} // namespace Engine::System
```
This class encapsulates a **`UI`** system dedicated to managing user interface functionalities within an ECS-based structure. It oversees the configuration, processing, and handling of UI-related elements, including buttons, their states, visual effects, and user interactions, within the broader context of a game or application system.

**UI Class:**

**Inheritance:**

- Inherits from **`ECS::BaseSystem`**.

**Constructors:**

- **`UI(ECS::World &world)`**: Constructs the **`UI`** system, initializing it with a reference to an **`ECS::World`**.

**Methods:**

- **`void configure(ECS::World &world) override`**: Configures the system, accepting a world reference as a parameter.
- **`void unconfigure() override`**: Manages the unconfiguration or resetting of the system.
- **`void tick() override`**: Executes the system's logic during each iteration.
- **`void handleStartGame()`**: Handles the initiation of the game.
- **`void updateButtonState(ECS::ComponentHandle<Components::ButtonComponent> buttonComp, ECS::ComponentHandle<Components::RenderableComponent> renderable, const sf::Vector2f &worldPos)`**: Updates the state of buttons.
- **`void resetButtonVisual(ECS::ComponentHandle<Components::RenderableComponent> renderable)`**: Resets the visual state of buttons.
- **`void hoverEffect(ECS::ComponentHandle<Components::ButtonComponent> buttonComp, ECS::ComponentHandle<Components::RenderableComponent> renderable)`**: Executes the hover effect on buttons.
- **`void handleClick(ECS::ComponentHandle<Components::ButtonComponent> buttonComp, ECS::ComponentHandle<Components::RenderableComponent> renderable)`**: Handles button click events.

# WorldMovement.system.hpp
```cpp
#pragma once

#include "ECS/Components.hpp"
#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Renderable.component.hpp"

namespace Engine::System
{
    class WorldMoveSystem : public ECS::BaseSystem
    {
        public:
            WorldMoveSystem(ECS::World &world) : ECS::BaseSystem(world){};
            WorldMoveSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~WorldMoveSystem() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

        private:
    };
} // namespace Engine::System
```
The class encompasses a system dedicated to controlling and managing the movement and progression of the game's world elements within the ECS framework. It's responsible for configuring, updating, and processing the movement-related logic necessary for the game world to progress, evolve, or change over time during gameplay.

**WorldMoveSystem Class:**

**Inheritance:**

- Inherits from **`ECS::BaseSystem`**.

**Constructors:**

- **`WorldMoveSystem(ECS::World &world)`**: Constructs the **`WorldMoveSystem`**, initializing it with a reference to an **`ECS::World`**.

**Methods:**

- **`void configure(ECS::World &world) override`**: Configures the system, accepting a world reference as a parameter.
- **`void unconfigure() override`**: Manages the unconfiguration or resetting of the system.
- **`void tick() override`**: Executes the system's logic during each iteration.

