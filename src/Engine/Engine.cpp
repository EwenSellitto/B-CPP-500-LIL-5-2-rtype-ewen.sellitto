/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Engine.cpp
*/

#include "Engine/Engine.hpp"

#include <SFML/Window/Event.hpp>
#include <vector>

#include "ECS/Entity.hpp"
#include "ECS/World.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "Engine/Events/Resize.event.hpp"
#include "Engine/Systems/Renderer.system.hpp"

using namespace Engine;

/*===================//
//  Singleton Logic  //
//===================*/

EngineClass &EngineClass::getEngine()
{
    static EngineClass engine = EngineClass();
    return engine;
}

EngineClass &EngineClass::getEngine(std::size_t x, std::size_t y, std::string name)
{
    static EngineClass engine = EngineClass(x, y, name);
    return engine;
}

/*============================//
//  Constructor / Destructor  //
//============================*/

EngineClass::EngineClass(const std::size_t window_size_x, const std::size_t window_size_y,
                         const std::string window_name, std::string start_world)
    : window(sf::RenderWindow(sf::VideoMode(window_size_x, window_size_y), window_name,
                              sf::Style::Close | sf::Style::Resize)),
      _running(false), _fullscreen(false), _worldsFactories(), _currentWorld(), _startWorld(start_world),
      _windowSizeX(window_size_x), _windowSizeY(window_size_y), _global_entities()
{
    window.setFramerateLimit(60);
}

EngineClass::~EngineClass()
{
    window.close();
}

/*===================//
//  Getters/Setters  //
//===================*/

void EngineClass::setStartWorld(const std::string &name)
{
    _startWorld = name;
}

/**
 * @brief Get the Window Size X object
 * @return std::size_t
 */
std::size_t EngineClass::getWindowSizeX()
{
    return _windowSizeX;
}

/**
 * @brief Get the Window Size Y object
 * @return std::size_t
 */
std::size_t EngineClass::getWindowSizeY()
{
    return _windowSizeY;
}

/*===================//
//  Worlds Handling  //
//===================*/

/**
 * @brief Creates an empty world with the given name
 * @param name The name of the world
 * @return void
 * @note If the world already exists, it will be overwritten
 * @note This function will throw an error if the world doesn't exist
 */
void EngineClass::createEmptyWorld(const std::string name)
{
    _currentWorld = std::make_pair(name, new ECS::World());
}

/**
 * @brief Adds a world factory to the engine
 * @param name The name of the world
 * @param factory The factory function
 * @return void
 * @note The factory function must return a shared_ptr to a world
 * @note If the world already exists, it will be overwritten
 */
void EngineClass::addWorldFactory(std::string name, std::function<ECS::World *()> factory)
{
    _worldsFactories[name] = factory;
}

/**
 * @brief Switches the current world to the one with the given name
 * @param name The name of the world to switch to
 * @throw std::runtime_error if the world doesn't exist
 * @return void
 * @note This function will throw an error if the world doesn't exist
 * @note You can define DONT_ADD_RENDERER_SYSTEM to not add the renderer system to the world automatically
 */
void EngineClass::switchWorld(const std::string name)
{
    auto it = _worldsFactories.find(name);
    auto c  = _currentWorld;
    if (it == _worldsFactories.end()) throw std::runtime_error("World not found");
    _currentWorld = std::make_pair(name, it->second());

#ifdef ADD_RENDERER_SYSTEM
    _currentWorld.second->addSystem<System::Renderer>("Renderer");
#endif

    _pending_destroy.push_back(c);
}

std::vector<std::string> EngineClass::getWorldsNames()
{
    std::vector<std::string> names;
    for (auto &it : _worldsFactories)
        names.push_back(it.first);
    return names;
}

ECS::World &EngineClass::world()
{
    return *_currentWorld.second;
}

/*===================//
//  Events handling  //
//===================*/

void EngineClass::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
#ifdef BIND_F11_TO_FULLSCREEN
                if (event.key.code == sf::Keyboard::F11)
                    toggleFullscreen();
                else
#endif
#ifdef BIND_ESC_TO_CLOSE
                    if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                else
#endif

                    world().broadcastEvent<sf::Event::KeyEvent>(event.key);
                world().broadcastEvent<KeyPressedEvent>(KeyPressedEvent{event.key});
                break;

            case sf::Event::Resized:
                world().broadcastEvent<ResizeEvent>(ResizeEvent(event.size.width, event.size.height));
                break;

            case sf::Event::KeyReleased:
                world().broadcastEvent<KeyReleasedEvent>(KeyReleasedEvent{event.key});
                break;

            case sf::Event::TextEntered:
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
            case sf::Event::MouseWheelMoved:
            case sf::Event::MouseWheelScrolled:
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            case sf::Event::MouseMoved:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickMoved:
            case sf::Event::JoystickConnected:
            case sf::Event::JoystickDisconnected:
            case sf::Event::TouchBegan:
            case sf::Event::TouchMoved:
            case sf::Event::TouchEnded:
            case sf::Event::SensorChanged:
            case sf::Event::Count:
            default:
                break;
        }
    }
}

/*=================//
//  General Logic  //
//=================*/

void EngineClass::run()
{
    if (_worldsFactories.empty())
        createEmptyWorld("default");
    else if (_currentWorld.second == nullptr)
        switchWorld(_startWorld);

    while (window.isOpen()) {
        destroyPendingWorlds();
        handleEvents();
        world().tick();
    }
}

void EngineClass::toggleFullscreen()
{
    _fullscreen       = !_fullscreen;
    ResizeEvent event = {0, 0};

    window.close();
    if (_fullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), "default",
                      sf::Style::Fullscreen | sf::Style::Close | sf::Style::Resize);
        event = ResizeEvent(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    } else {
        event = ResizeEvent(_windowSizeX, _windowSizeY);
        window.create(sf::VideoMode(_windowSizeX, _windowSizeY), "default", sf::Style::Close | sf::Style::Resize);
    }
    world().broadcastEvent<ResizeEvent>(event);
}

/*===================//
//  Private Methods  //
//===================*/

void EngineClass::destroyPendingWorlds()
{
    if (_pending_destroy.empty()) return;
    for (auto &world : _pending_destroy)
        delete world.second;
    _pending_destroy.clear();
}

/*=========================//
//  GlobalEntity Handling  //
//=========================*/

/**
 * @brief Add a global entity to the world.
 *
 * @param entity A unique pointer to the GlobalEntity to be added. Ownership of the global entity is
 * transferred to the World.
 * @return id_t The unique identifier for the added global entity.
 */
id_t EngineClass::addGlobalEntity(std::unique_ptr<ECS::GlobalEntity> entity)
{
    ECS::type_t id = ECS::Utils::getNewId<ECS::GlobalEntity>();

    _global_entities.emplace(id, std::move(entity));
    return id;
}

/**
 * @brief Remove a global entity from the world.
 *
 * @param id The unique identifier of the global entity to be removed.
 * @note The global entity will be properly destroyed when removed from all the worlds.
 */
void EngineClass::removeGlobalEntity(id_t id)
{
    _global_entities.erase(id);
}

/**
 * @brief Get an immutable reference to a global entity.
 *
 * @param id The unique identifier of the global entity to get.
 * @return const GlobalEntity& An immutable reference to the global entity.
 */
const ECS::GlobalEntity &EngineClass::getGlobalEntity(id_t id)
{
    return *_global_entities.at(id);
}

/**
 * @brief Get a mutable reference to a global entity.
 *
 * @param id The unique identifier of the global entity to get.
 * @return GlobalEntity& A mutable reference to the global entity.
 */
ECS::GlobalEntity &EngineClass::getMutGlobalEntity(id_t id)
{
    return *_global_entities.at(id);
}

/**
 * @brief Get all global entities that have a specific component type.
 *
 * @tparam T The component type to filter global entities.
 * @return std::vector<GlobalEntity *> A vector of pointers to the global entities.
 */
template <typename T> std::unordered_map<ECS::GlobalEntity *, ECS::ComponentHandle<T>> EngineClass::getGlobal()
{
    std::unordered_map<ECS::GlobalEntity *, ECS::ComponentHandle<T>> entities;
    for (auto &pair : _global_entities) {
        ECS::GlobalEntity &entity = *pair.second;
        if (entity.has<T>()) {
            ECS::ComponentHandle<T> component = entity.getComponent<T>();
            entities.emplace(&entity, component);
        }
    }
    return entities;
}

/**
 * @brief Iterates over all entities that have a specific component type.
 *
 * @tparam T The component type to filter entities.
 * @param func The callable function that will be applied to each global entity and its component.
 */
template <typename T> void EngineClass::each(std::function<void(ECS::GlobalEntity *, ECS::ComponentHandle<T>)> func)
{
    for (auto &pair : _global_entities) {
        ECS::GlobalEntity &entity = *pair.second;
        if (entity.has<T>()) {
            ECS::ComponentHandle<T> component = entity.getComponent<T>();
            func(&entity, component);
        }
    }
}

/**
 * @brief Iterates over all entities that have a specific set of component types.
 *
 * @tparam Types Component types to filter entities.
 * @param func The callable function that will be applied to each global entity and its components.
 * @note This function utilizes a helper function to handle the iteration and application of the
 function.
 */
template <typename... Types>
void EngineClass::each(std::function<void(ECS::GlobalEntity *, ECS::ComponentHandle<Types...>)> func)
{
    for (auto &pair : _global_entities) {
        ECS::GlobalEntity &entity = *pair.second;
        if (entity.has<Types...>()) {
            _eachHelper<Types...>(&entity, func);
        }
    }
}

/**
 * @brief get all entities that have a set of given components.
 *
 * @tparam Types The component types to filter entities.
 * @return std::vector<Entity *> A vector of pointers to the entities.
 */
template <typename... Types> std::vector<ECS::GlobalEntity *> EngineClass::getGlobalEntitiesWithComponents()
{
    std::vector<ECS::GlobalEntity *> entities;
    for (auto &pair : _global_entities) {
        ECS::GlobalEntity &entity = *pair.second;
        if (entity.has<Types...>()) {
            entities.push_back(&entity);
        }
    }
    return entities;
}

/**
 * @brief get the first entity that have a set of given components.
 *
 * @tparam Types The component types to filter entities.
 * @return Entity * A pointer to the entity.
 */
template <typename... Types> ECS::GlobalEntity *EngineClass::getGlobalEntityWithComponents()
{
    std::vector<ECS::GlobalEntity *> entities = getGlobalEntitiesWithComponents<Types...>();

    if (entities.empty()) return nullptr;
    return entities[0];
}

/*==========================//
//  Private Helper Methods  //
//==========================*/

/**
 * @brief Helper function to call a function on a global entity with a single component type.
 *
 * @tparam T The component type.
 * @param g_entity Pointer to the entity.
 * @param func The function to be applied to the global entity and its component.
 */
template <typename T>
void EngineClass::_eachHelper(ECS::GlobalEntity                                                *g_entity,
                              std::function<void(ECS::GlobalEntity *, ECS::ComponentHandle<T>)> func)
{
    func(&g_entity, g_entity->getComponent<T>());
}

/**
 * @brief Recursive helper function to call a function on a global entity with multiple component types.
 *
 * @tparam T The current component type being processed.
 * @tparam V The next component type to be processed.
 * @tparam Types Remaining component types to be processed.
 * @param g_entity Pointer to the entity.
 * @param func The function to be applied to the global entity and its component.
 * @note This function recursively iterates through the component types.
 */
template <typename T, typename V, typename... Types>
void EngineClass::_eachHelper(ECS::GlobalEntity                                                *g_entity,
                              std::function<void(ECS::GlobalEntity *, ECS::ComponentHandle<T>)> func)
{
    g_entity->has<T>() ? _eachHelper<T>(g_entity, func) : nullptr;
    _eachHelper<V, Types...>(g_entity, func);
}
