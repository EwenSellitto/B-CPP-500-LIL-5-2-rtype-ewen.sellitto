# Engine/Components Technical Documentation

# Animation.component.hpp

```cpp
#pragma once

#include "ECS/Components.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"

namespace Engine::Components
{
    struct AnimationComponent : ECS::BaseComponent {
        public:
            AnimationComponent() = default;
            AnimationComponent(int x, int y, int width, int height, int tx, int ty, int animationSpeed, int frameCount)
                : textureRect(x, y, width, height), tileSize(tx, ty), animationSpeed(animationSpeed),
                  frameCount(frameCount){};
            ~AnimationComponent() = default;

            sf::Rect<int> textureRect = {0, 0, 0, 0};
            sf::Vector2i  tileSize    = {0, 0};
            int           frame{0};
            int           animationSpeed{0};
            int           frameCount{0};
            sf::Clock     clock{};
    };
} // namespace Engine::Components
```
The **`AnimationComponent`** belongs to the **`Engine::Components`** namespace and is a fundamental structure representing an entity's animation properties within the game engine.

### **Member Variables:**

- **`sf::Rect<int> textureRect = {0, 0, 0, 0}`**: Defines the rectangular region on a texture that the animation utilizes.
- **`sf::Vector2i tileSize = {0, 0}`**: Represents the size of each frame or tile within the texture.
- **`int frame{0}`**: Current frame index for the animation.
- **`int animationSpeed{0}`**: Speed of the animation.
- **`int frameCount{0}`**: Total number of frames in the animation.
- **`sf::Clock clock{}`**: Clock instance to manage the animation timing.

### **Constructors:**

- **`AnimationComponent() = default;`**: Default constructor.
- **`AnimationComponent(int x, int y, int width, int height, int tx, int ty, int animationSpeed, int frameCount)`**: Custom constructor initializing the animation with specific parameters for textureRect, tileSize, animationSpeed, and frameCount.

# Button.component.hpp

```cpp
#pragma once
#include <functional>
#include <string>

#include "ECS/Components.hpp"

enum class ButtonType {
    Simple
};

namespace Engine::Components
{
    struct ButtonComponent : public ECS::BaseComponent {
            std::string           text;
            std::function<void()> onClick;
            bool                  isHovered = false;
            bool                  isClicked = false;

            ButtonComponent(const std::string &text, std::function<void()> onClick) : text(text), onClick(onClick) {}
    };
} // namespace Engine::Components
```
The **`ButtonComponent`** resides in the **`Engine::Components`** namespace and represents an essential entity component that defines a button's behavior within the game engine.

### **Member Variables:**

- **`std::string text`**: Holds the text or label associated with the button.
- **`std::function<void()> onClick`**: Represents the function to be executed upon clicking the button.
- **`bool isHovered = false`**: Indicates whether the button is currently being hovered over.
- **`bool isClicked = false`**: Indicates whether the button has been clicked.

### **Constructor:**

- **`ButtonComponent(const std::string &text, std::function<void()> onClick)`**: Constructor initializing the button component with specified text and an onClick function.

# Collision.component.hpp

```cpp
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <string>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Rect.hpp"

namespace Engine::Components
{
    struct CollisionComponent : public ECS::BaseComponent {
        public:
            explicit CollisionComponent(float off_x = 0, float off_y = 0, float size_x = 0, float size_y = 0)
                : rect(off_x, off_y, size_x, size_y)
            {
            }

            ~CollisionComponent() override = default;

            sf::FloatRect rect;
    };
} // namespace Engine::Components

struct SpriteInfo {
        std::string filePath;
        int         width;
        int         height;
        int         oneframeX;
        int         oneframeY;
        int         nbFrames;
        int         offsetX;
        int         offsetY;
};

static const std::map<std::string, SpriteInfo> spriteInfoMap = {
    {"Asteroid-Flame", {"./assets/Environnement/Asteroid-Flame.png", 288, 96, 96, 96, 3, 36, 30}},
    {"Asteroid01-Base", {"./assets/Environnement/Asteroid01-Base.png", 96, 96, 96, 96, 1, 28, 31}},
    {"Klaed-Battlecruiser-Base", {"./assets/klaed/Klaed-Battlecruiser-Base.png", 128, 128, 128, 128, 1, 27, 12}},
    {"Klaed-Battlecruiser-Destruction",
     {"./assets/klaed/Klaed-Battlecruiser-Destruction.png", 1792, 128, 128, 128, 14, 27, 12}},
    {"Klaed-Bullet", {"./assets/klaed/Klaed-Bullet.png", 16, 16, 4, 16, 4, 1, 4}},
    {"Klaed-Bomber-Base", {"./assets/klaed/Klaed-Bomber-Base.png", 64, 64, 64, 64, 1, 17, 20}},
    {"Klaed-Bomber-Destruction", {"./assets/klaed/Klaed-Bomber-Destruction.png", 512, 64, 64, 64, 8, 0, 0}},
    {"Klaed-Dreadnought-Base", {"./assets/klaed/Klaed-Dreadnought-Base.png", 128, 128, 128, 128, 1, 28, 13}},
    {"Klaed-Dreadnought-Destruction",
     {"./assets/klaed/Klaed-Dreadnought-Destruction.png", 1536, 128, 128, 128, 12, 0, 0}},
    {"Klaed-Fighter-Base", {"./assets/klaed/Klaed-Fighter-Base.png", 64, 64, 64, 64, 1, 20, 21}},
    {"Klaed-Fighter-Destruction", {"./assets/klaed/Klaed-Fighter-Destruction.png", 576, 64, 64, 64, 9, 0, 0}},
    {"Klaed-Frigate-Base", {"./assets/klaed/Klaed-Frigate-Base.png", 64, 64, 64, 64, 1, 14, 11}},
    {"Klaed-Frigate-Destruction", {"./assets/klaed/Klaed-Frigate-Destruction.png", 576, 64, 64, 64, 9, 0, 0}},
    {"Klaed-Scout-Base", {"./assets/klaed/Klaed-Scout-Base.png", 64, 64, 64, 64, 1, 21, 23}},
    {"Klaed-Scout-Destruction", {"./assets/klaed/Klaed-Scout-Destruction.png", 640, 64, 64, 64, 10, 0, 0}},
    {"Klaed-Supportship-Base", {"./assets/klaed/Klaed-Supportship-Base.png", 64, 64, 64, 64, 1, 18, 15}},
    {"Klaed-Supportship-Destruction", {"./assets/klaed/Klaed-Supportship-Destruction.png", 640, 64, 64, 64, 10, 0, 7}},
    {"Klaed-TorpedoShip-Base", {"./assets/klaed/Klaed-TorpedoShip-Base.png", 64, 64, 64, 64, 1, 4, 21}},
    {"Klaed-TorpedoShip-Destruction", {"./assets/klaed/Klaed-TorpedoShip-Destruction.png", 640, 64, 64, 64, 10, 0, 0}},
    {"MainShip-Base-Fullhealth", {"./assets/MainShip/MainShip-Base-Fullhealth.png", 48, 48, 48, 48, 1, 9, 11}},
    {"MainShip-Base-Destruction", {"./assets/MainShip/MainShip-Base-Destruction.png", 672, 48, 48, 48, 14, 9, 11}},
    {"MainshipWeapon-Projectile-Autocannonbullet",
     {"./assets/MainShipWeapons/MainshipWeapon-Projectile-Autocannonbullet.png", 128, 32, 32, 32, 4, 15, 12}}};
```
The **`CollisionComponent`** resides in the **`Engine::Components`** namespace and represents a component dedicated to handling collision detection within the game engine.

### **Member Variables:**

- **`sf::FloatRect rect`**: Represents the collision box, defined by its position and size.

### **Constructor:**

- **`explicit CollisionComponent(float off_x = 0, float off_y = 0, float size_x = 0, float size_y = 0)`**: Constructor initializing the collision component with the specified offset and size.

### spriteInfoMap:

This map holds information regarding various sprites used in the game, providing details like file paths, dimensions, frame sizes, and offsets for different entities.

The **`spriteInfoMap`** contains pairs of string keys (representing the sprite name) and corresponding **`SpriteInfo`** structures.

### **SpriteInfo Structure:**

The **`SpriteInfo`** structure encapsulates essential information for rendering sprites.

- **`std::string filePath`**: File path to the sprite's image file.
- **`int width`**: Width of the sprite.
- **`int height`**: Height of the sprite.
- **`int oneframeX`**: Width of one frame within the sprite.
- **`int oneframeY`**: Height of one frame within the sprite.
- **`int nbFrames`**: Number of frames within the sprite.
- **`int offsetX`**: X-axis offset.
- **`int offsetY`**: Y-axis offset.

This map serves as a centralized repository for sprite-related data, allowing easy access to sprite information throughout the game.

# ExcludeCollision.component.hpp

```cpp
#pragma once

#include "ECS/Components.hpp"
namespace Engine::Components
{
    class ExcludeCollisionComponent : public ECS::BaseComponent
    {
        public:
            ExcludeCollisionComponent(std::size_t id) : id(id) {}
            ~ExcludeCollisionComponent() override = default;

            std::size_t id;
    };
} // namespace Engine::Components
```
The **`ExcludeCollisionComponent`** resides in the **`Engine::Components`** namespace and represents a component that excludes specific entities from collision handling.

### **Member Variables:**

- **`std::size_t id`**: Represents the identifier of the entity excluded from collision.

### **Constructor:**

- **`ExcludeCollisionComponent(std::size_t id)`**: Constructor initializing the exclusion component with the specified entity identifier.

This component assists in managing collision detection by excluding specific entities from collision calculations or interactions.

# Moving.component.hpp
```cpp
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct MovingComponent : public ECS::BaseComponent {
        public:
            MovingComponent(sf::Vector2f initialPos, size_t moveDuration, sf::Vector2f moveAmount)
                : initialPos(initialPos), moveAmount(moveAmount), moveDuration(moveDuration)
            {
                if (moveDuration == 0) this->moveDuration = 1;
                auto now      = std::chrono::high_resolution_clock::now();
                auto epoch    = now.time_since_epoch();
                moveStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
            }

            ~MovingComponent() override = default;

            size_t       moveStartTime;
            sf::Vector2f initialPos;
            sf::Vector2f moveAmount;
            size_t       moveDuration;

        private:
    };
} // namespace Engine::Components
```
The **`MovingComponent`** resides in the **`Engine::Components`** namespace and represents a component that manages the movement of entities.

### **Member Variables:**

- **`size_t moveStartTime`**: Represents the starting time of the movement, measured in milliseconds since the epoch.
- **`sf::Vector2f initialPos`**: Defines the initial position of the entity.
- **`sf::Vector2f moveAmount`**: Indicates the amount of movement in the x and y directions.
- **`size_t moveDuration`**: Defines the duration of the movement in milliseconds.

### **Constructor:**

- **`MovingComponent(sf::Vector2f initialPos, size_t moveDuration, sf::Vector2f moveAmount)`**: Constructor initializing the movement component with the provided initial position, movement duration, and movement amount.
    - **`initialPos`**: The initial position of the entity.
    - **`moveDuration`**: The duration for which the movement lasts.
    - **`moveAmount`**: The distance and direction of the movement.

This component manages entity movement based on the provided parameters, including the starting time of the movement, initial position, movement amount, and duration.

# Parallax.component.hpp
```cpp
#pragma once
#include "ECS/Components.hpp"

enum class ParallaxLayer {
    FarBackground,
    MidBackground,
    NearBackground
};

namespace Engine::Components
{
    struct ParallaxComponent : public ECS::BaseComponent {
            ParallaxLayer layer;
            float         speed;
            sf::Vector2f  offset;
            bool          first;

            ParallaxComponent(ParallaxLayer layer, float speed) : layer(layer), speed(speed), offset(0, 0) {}
    };
} // namespace Engine::Components
```
The **`ParallaxComponent`** resides within the **`Engine::Components`** namespace and represents a component responsible for parallax scrolling effects in different layers.

### **Member Variables:**

- **`ParallaxLayer layer`**: Specifies the layer of the parallax effect (**`FarBackground`**, **`MidBackground`**, or **`NearBackground`**).
- **`float speed`**: Indicates the speed at which the layer moves relative to the main view.
- **`sf::Vector2f offset`**: Represents the offset in the x and y directions for the parallax effect.
- **`bool first`**: Indicates whether this is the first instance of the parallax effect.

### **Constructor:**

- **`ParallaxComponent(ParallaxLayer layer, float speed)`**: Constructor initializing the parallax component with the provided layer and speed.
    - **`layer`**: The layer of the parallax effect (**`FarBackground`**, **`MidBackground`**, or **`NearBackground`**).
    - **`speed`**: The speed at which the layer moves relative to the main view.

This component handles the parallax scrolling effect by specifying the layer, speed, and offset for different layers of background elements in the game, contributing to the overall visual depth and motion in the environment.

# Position.component.hpp
```cpp
#pragma once

#include "ECS/Components.hpp"

namespace Engine::Components
{
    typedef std::pair<long int, long int> PositionComponent_serialized_t;

    struct PositionComponent : public ECS::BaseComponent {
        public:
            PositionComponent() : x(0), y(0){};
            explicit PositionComponent(int x, int y) : x(x), y(y){};
            ~PositionComponent() override = default;

            static PositionComponent_serialized_t serialize(PositionComponent &data)
            {
                return std::make_pair(data.x, data.y);
            }

            static PositionComponent deserialize(PositionComponent_serialized_t data)
            {
                return PositionComponent(data.first, data.second);
            }

            int x;
            int y;
    };
} // namespace Engine::Components
```
The **`PositionComponent`** belongs to the **`Engine::Components`** namespace and represents a component responsible for storing position data in a 2D space.

### **Member Variables:**

- **`int x`**: Represents the x-coordinate of the position.
- **`int y`**: Represents the y-coordinate of the position.

### **Constructors:**

- **`PositionComponent()`**: Default constructor initializing the position at (0, 0).
- **`PositionComponent(int x, int y)`**: Constructor initializing the position with the specified x and y coordinates.

### **Static Methods:**

- **`static PositionComponent_serialized_t serialize(PositionComponent &data)`**: Converts the position component data into a serialized form (pair of x and y coordinates).
- **`static PositionComponent deserialize(PositionComponent_serialized_t data)`**: Converts serialized data (pair of x and y coordinates) back into a **`PositionComponent`**.

This component is used to manage and store position-related information for entities in a 2D space within the game world. It offers functionality to serialize and deserialize its data for potential use cases like network transmission or saving game states.

# Renderable.component.hpp
```cpp
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct RenderableComponent : public ECS::BaseComponent {
        public:
            RenderableComponent()
                : sprite(), size({0, 0}), position({0, 0}), priority(0), rotation(0), scale({1, 1}), isDisplayed(false),
                  path()
            {
            }

            RenderableComponent(const std::string &texture_path, float pos_x, float pos_y, int priority,
                                float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false)
                : texture(), sprite(), size(), position({pos_x, pos_y}), priority(priority), rotation(rotation),
                  scale(scale), isDisplayed(true), path(texture_path), setOrigin(setOrigin)

            {
                setTexture(texture_path);
            };

            RenderableComponent(const std::string &texture_path, sf::Vector2<float> pos, int priority,
                                float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false)
                : texture(), sprite(), size(), position(pos), priority(priority), rotation(rotation), scale(scale),
                  isDisplayed(true), path(texture_path), setOrigin(setOrigin)

            {
                setTexture(texture_path);
            }

            ~RenderableComponent() override = default;

            sf::Texture              texture;
            sf::Sprite               sprite;
            sf::Vector2<std::size_t> size;
            sf::Vector2<float>       position;
            int                      priority;
            float                    rotation;
            sf::Vector2<float>       scale;
            bool                     isDisplayed;
            std::string              path;
            bool                     setOrigin = false;

        private:
            void setTexture(const std::string &texture_path)
            {
                if (!texture.loadFromFile(texture_path))
                    throw std::runtime_error("Cannot load texture " + texture_path);
                sprite = sf::Sprite(texture);
                sprite.setScale(scale.x, scale.y);
                sprite.setPosition(position.x, position.y);
                sprite.setRotation(rotation);
                size = {texture.getSize().x, texture.getSize().y};
                if (setOrigin) sprite.setOrigin(size.x / 2, size.y / 2);
            }
    };
} // namespace Engine::Components
```
The **`RenderableComponent`** is part of the **`Engine::Components`** namespace, serving as a component responsible for rendering entities within the game world.

### Member Variables:

- **`sf::Texture texture`**: Represents the texture associated with the rendered entity.
- **`sf::Sprite sprite`**: Represents the sprite used for rendering the entity.
- **`sf::Vector2<std::size_t> size`**: Represents the size of the rendered entity.
- **`sf::Vector2<float> position`**: Represents the position of the rendered entity.
- **`int priority`**: Represents the priority level of rendering.
- **`float rotation`**: Represents the rotation angle of the rendered entity.
- **`sf::Vector2<float> scale`**: Represents the scaling factor of the rendered entity.
- **`bool isDisplayed`**: Indicates whether the entity should be displayed/rendered.
- **`std::string path`**: Stores the file path of the texture.
- **`bool setOrigin`**: Indicates if the origin point is set.

### Constructors:

- **`RenderableComponent()`**: Default constructor initializing various rendering-related variables.
- **`RenderableComponent(const std::string &texture_path, float pos_x, float pos_y, int priority, float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false)`**: Constructs a renderable component with specified parameters.
- **`RenderableComponent(const std::string &texture_path, sf::Vector2<float> pos, int priority, float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false)`**: Constructs a renderable component with texture path, position, priority, rotation, scale, and origin setting.

### Methods:

- **`void setTexture(const std::string &texture_path)`**: Helper method to set the texture of the sprite based on the given texture path. It sets other rendering attributes like position, rotation, size, and origin accordingly.

This component encapsulates rendering functionality, including handling textures, sprites, positions, rotations, scaling, and display settings for entities within the game world.

# Speed.component.hpp
```cpp
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct SpeedComponent : public ECS::BaseComponent {
        public:
            SpeedComponent(float speed) : speed(speed) {}

            ~SpeedComponent() override = default;

            float speed;

        private:
    };
} // namespace Engine::Components
```
The **`SpeedComponent`** belongs to the **`Engine::Components`** namespace and serves as a component responsible for representing the speed attribute of entities in the game.

### Member Variables:

- **`float speed`**: Represents the speed value associated with the entity.

### Constructors:

- **`SpeedComponent(float speed)`**: Initializes the **`speed`** attribute with the provided value.

This component is focused on encapsulating and storing the speed attribute for entities within the game. It allows for the management and manipulation of speed-related functionalities for specific entities.

# View.component.hpp
```cpp
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct ViewComponent : public ECS::BaseComponent {
        public:
            ViewComponent() : position(), view()
            {
                view.setCenter(sf::Vector2f(400, 300));
                view.setSize(sf::Vector2f(800, 600));
            }

            ViewComponent(sf::Vector2<float> position, sf::Vector2<float> size) : position(position), view()
            {
                view.setCenter(sf::Vector2f(position.x, position.y));
                view.setSize(sf::Vector2f(size.x, size.y));
            }

            ~ViewComponent() override = default;

            sf::Vector2<float> position;
            sf::View           view;

        private:
    };
} // namespace Engine::Components
```
The **`ViewComponent`** belongs to the **`Engine::Components`** namespace and serves as a component responsible for managing the game's view or camera settings.

### Member Variables:

- **`sf::Vector2<float> position`**: Represents the position of the view.
- **`sf::View view`**: Stores the actual view object responsible for managing the camera settings.

### Constructors:

- **`ViewComponent()`**: Initializes the view with default values:
    - Sets the center of the view to (400, 300).
    - Sets the size of the view to (800, 600).
- **`ViewComponent(sf::Vector2<float> position, sf::Vector2<float> size)`**: Allows initializing the view with specific position and size parameters.
    - Sets the center of the view to the provided **`position`**.
    - Sets the size of the view to the provided **`size`**.

This component encapsulates the view or camera settings used in the game. It provides flexibility to set and manage the view's position and size, allowing control over what portion of the game world is visible to the player.

# WorldMoveProgress.component.hpp
```cpp
#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct WorldMoveProgressComponent : public ECS::BaseComponent {
        public:
            WorldMoveProgressComponent() : progress(0) {}
            WorldMoveProgressComponent(size_t startingTime, size_t progress, size_t speed)
                : startingTime(startingTime), progress(progress), speed(speed)
            {
            }

            ~WorldMoveProgressComponent() override = default;

            // in epoch milliseconds
            size_t startingTime;

            // this is the progress of the world in the x-axis,
            // the walls, enemies are spawning because of it.
            size_t progress;
            // speed in +x per second.
            size_t speed;

        private:
    };
} // namespace Engine::Components
```
The **`WorldMoveProgressComponent`** belongs to the **`Engine::Components`** namespace and serves as a component responsible for managing the progress of the game world movement.

### Member Variables:

- **`size_t startingTime`**: Represents the starting time of the world movement, measured in epoch milliseconds.
- **`size_t progress`**: Represents the progress of the world in the x-axis. This progress is associated with spawning walls and enemies.
- **`size_t speed`**: Represents the speed of movement in the positive x-direction, measured in units per second.

### Constructors:

- **`WorldMoveProgressComponent()`**: Initializes the progress component with a default progress value of 0.
- **`WorldMoveProgressComponent(size_t startingTime, size_t progress, size_t speed)`**: Allows initializing the component with specific starting time, progress, and speed parameters.

This component plays a crucial role in managing the progression of the game world. The **`progress`** variable, associated with the x-axis, determines when and where certain game elements (such as walls and enemies) should spawn. The **`speed`** variable defines the rate at which the world progresses in the positive x-direction. The starting time (**`startingTime`**) provides a reference point for the beginning of world movement.