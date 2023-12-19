/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Engine.hpp
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstddef>
#include <memory>
#include <unordered_map>

#include "ECS/World.hpp"

class Engine
{
    public:
        Engine()
            : _currentWorld(nullptr),
              _window(sf::RenderWindow(sf::VideoMode(1920, 1080), "default", sf::Style::Close | sf::Style::Resize)),
              _worlds()
        {
        }

        Engine(std::size_t x, std::size_t y, std::string name)
            : _currentWorld(),
              _window(sf::RenderWindow(sf::VideoMode(x, y), name, sf::Style::Close | sf::Style::Resize)), _worlds()
        {
        }

        ~Engine()
        {
            _window.close();
        }

    private:
        std::shared_ptr<ECS::World>                                  _currentWorld;
        sf::RenderWindow                                             _window;
        std::unordered_map<std::string, std::shared_ptr<ECS::World>> _worlds;
};
