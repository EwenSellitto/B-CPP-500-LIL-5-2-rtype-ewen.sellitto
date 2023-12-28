/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Engine.cpp
*/

#include "Engine/Engine.hpp"

#include <SFML/Window/Event.hpp>
#include <vector>

#include "ECS/World.hpp"
#include "Engine/Events/Resize.event.hpp"

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
      _windowSizeX(window_size_x), _windowSizeY(window_size_y)
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

/*===================//
//  Worlds Handling  //
//===================*/

void EngineClass::createEmptyWorld(const std::string name)
{
    _currentWorld = std::make_pair(name, std::make_unique<ECS::World>());
}

void EngineClass::addWorldFactory(std::string name, std::function<std::shared_ptr<ECS::World>()> factory)
{
    _worldsFactories[name] = factory;
}

void EngineClass::switchWorld(const std::string name)
{
    auto it = _worldsFactories.find(name);
    if (it == _worldsFactories.end()) throw std::runtime_error("World not found");
    _currentWorld = std::make_pair(name, it->second());
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
                break;

            case sf::Event::Resized:
                world().broadcastEvent<ResizeEvent>(ResizeEvent(event.size.width, event.size.height));
                break;

            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
            case sf::Event::TextEntered:
            case sf::Event::KeyReleased:
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
