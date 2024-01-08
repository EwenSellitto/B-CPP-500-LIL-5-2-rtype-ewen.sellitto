# Engine Technical Documentation

```cpp
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstddef>
#include <functional>
#include <memory>
#include <unordered_map>

namespace ECS
{
    class World;
}

#ifndef DEFAULT_WINDOW_SIZE_X
#define DEFAULT_WINDOW_SIZE_X 800
#endif

#ifndef DEFAULT_WINDOW_SIZE_Y
#define DEFAULT_WINDOW_SIZE_Y 600
#endif

#ifndef DEFAULT_WINDOW_NAME
#define DEFAULT_WINDOW_NAME "default"
#endif

#ifndef BIND_F11_TO_OTHER
#define BIND_F11_TO_FULLSCREEN
#endif

#ifndef BIND_ESC_TO_OTHER
#define BIND_ESC_TO_QUIT
#endif

#ifndef DONT_ADD_RENDERER_SYSTEM
#define ADD_RENDERER_SYSTEM
#endif

#define WINDOW Engine::EngineClass::getEngine().window

namespace Engine
{
    typedef std::unordered_map<std::string, std::function<ECS::World *()>> world_factories_t;
    typedef std::pair<std::string, ECS::World *>                           world_t;

    class EngineClass
    {
        public:
            /*===================//
            //  Singleton Logic  //
            //===================*/

            static EngineClass &getEngine();
            static EngineClass &getEngine(std::size_t x, std::size_t y, std::string name);

            EngineClass &operator=(const EngineClass &engine) = delete;
            EngineClass(const EngineClass &engine)            = delete;

        private:
            /*============================//
            //  Constructor / Destructor  //
            //============================*/

            EngineClass(std::size_t x = DEFAULT_WINDOW_SIZE_X, std::size_t y = DEFAULT_WINDOW_SIZE_Y,
                        std::string name = DEFAULT_WINDOW_NAME, std::string start_world = DEFAULT_WINDOW_NAME);

            ~EngineClass();

        public:
            /*===================//
            //  Getters/Setters  //
            //===================*/

            void setStartWorld(const std::string &name);

            std::size_t getWindowSizeX();
            std::size_t getWindowSizeY();

            /*===================//
            //  Worlds Handling  //
            //===================*/

            void createEmptyWorld(std::string name);

            void addWorldFactory(std::string name, std::function<ECS::World *()>);

            void switchWorld(std::string name);

            std::vector<std::string> getWorldsNames();

            ECS::World &world();

            /*=================//
            //  General Logic  //
            //=================*/

            void run();

            void toggleFullscreen();

            /*==================//
            //  Event Handling  //
            //==================*/

            void handleEvents();

            /*=====================//
            //  Public Attributes  //
            //=====================*/

            sf::RenderWindow window;

        private:
            /*==============//
            //  Attributes  //
            //==============*/

            bool                 _running;
            bool                 _fullscreen;
            world_factories_t    _worldsFactories;
            world_t              _currentWorld;
            std::vector<world_t> _pending_destroy;
            std::string          _startWorld;
            std::size_t          _windowSizeX;
            std::size_t          _windowSizeY;

            /*===================//
            //  Private Methods  //
            //===================*/

            void destroyPendingWorlds();
    };
} // namespace Engine
```

The **`EngineClass`** is a fundamental component responsible for orchestrating the game engine's functionalities, including window management, world handling, event processing, and game logic control.

### **Member Functions:**

- **`static EngineClass &getEngine()`**: Retrieves the instance of the game engine.
- **`static EngineClass &getEngine(std::size_t x, std::size_t y, std::string name)`**: Retrieves the instance of the game engine with customized window dimensions and name.
- **`EngineClass(const EngineClass &engine)`**: Deleted copy constructor to enforce the singleton pattern.
- **`EngineClass &operator=(const EngineClass &engine)`**: Deleted assignment operator to enforce the singleton pattern.
- **`~EngineClass()`**: Destructor for the EngineClass.

### **Getters/Setters:**

- **`void setStartWorld(const std::string &name)`**: Sets the initial world for the game engine.
- **`std::size_t getWindowSizeX()`**: Retrieves the X-axis size of the game window.
- **`std::size_t getWindowSizeY()`**: Retrieves the Y-axis size of the game window.

### **Worlds Handling:**

- **`void createEmptyWorld(std::string name)`**: Creates an empty world with the given name.
- **`void addWorldFactory(std::string name, std::function<ECS::World *()>)`**: Adds a factory method to create a specific world.
- **`void switchWorld(std::string name)`**: Switches the current world to the one specified.
- **`std::vector<std::string> getWorldsNames()`**: Retrieves the names of available worlds.
- **`ECS::World &world()`**: Retrieves the active world.

### **General Logic:**

- **`void run()`**: Initiates the game engine loop.
- **`void toggleFullscreen()`**: Toggles the game window between fullscreen and windowed mode.

### **Event Handling:**

- **`void handleEvents()`**: Manages the processing of events.

### **Public Attributes:**

- **`sf::RenderWindow window`**: Public attribute representing the game window.

### **Private Attributes:**

- **`bool _running`**: Boolean flag indicating whether the engine is running.
- **`bool _fullscreen`**: Boolean flag representing the current fullscreen/windowed mode.
- **`world_factories_t _worldsFactories`**: Collection of world factories for creating different worlds.
- **`world_t _currentWorld`**: Current active world.
- **`std::vector<world_t> _pending_destroy`**: List of worlds pending destruction.
- **`std::string _startWorld`**: Initial world name.
- **`std::size_t _windowSizeX`**: Width of the game window.
- **`std::size_t _windowSizeY`**: Height of the game window.

&nbsp;


# [Components Documentation](./Engine/Components.md)
# [Events Documentation](./Engine/Events.md)
# [Systems Documentation](./Engine/Systems.md)
