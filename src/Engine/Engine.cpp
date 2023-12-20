/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Engine.cpp
*/

#include "Engine/Engine.hpp"

#include <SFML/Window/Event.hpp>

#include "ECS/World.hpp"

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
                         const std::string window_name)
    : window(sf::RenderWindow(sf::VideoMode(window_size_x, window_size_y), window_name,
                              sf::Style::Close | sf::Style::Resize)),
      _running(false), _fullscreen(false), _currentWorld()
{
}

EngineClass::~EngineClass()
{
    window.close();
}

/*===================//
//  Worlds Handling  //
//===================*/

void EngineClass::createWorld(const std::string name)
{
    _currentWorld = std::make_pair(name, std::make_unique<ECS::World>());
}

ECS::World &EngineClass::world()
{
    return *_currentWorld.second;
}

/*=================//
//  General Logic  //
//=================*/

void EngineClass::run()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) toggleFullscreen();
        }
        world().tick();
    }
}

void EngineClass::toggleFullscreen()
{
    _fullscreen = !_fullscreen;
    window.close();
    if (window.getSize() == sf::Vector2u(1920, 1080)) {
        window.create(sf::VideoMode(1920, 1080), "default", sf::Style::Fullscreen);
    } else {
        window.create(sf::VideoMode(1920, 1080), "default", sf::Style::Close | sf::Style::Resize);
    }
}
