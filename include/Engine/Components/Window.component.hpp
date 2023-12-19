/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Screen.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

#include "ECS/Clock.hpp"
#include "ECS/Components.hpp"

namespace Engine::Components
{
    class WindowComponent : public ECS::BaseComponent
    {
        public:
            WindowComponent() : window(new sf::RenderWindow(sf::VideoMode(1920, 1080), "Default")), clock(){};
            WindowComponent(unsigned int size_x, unsigned int size_y, const std::string &title)
                : window(new sf::RenderWindow(sf::VideoMode(size_x, size_y), title)), clock(){};
            explicit WindowComponent(sf::VideoMode mode, const std::string &title = "Default")
                : window(new sf::RenderWindow(mode, title)), clock(){};
            WindowComponent(WindowComponent &&other) noexcept : clock()
            {
                window       = other.window;
                other.window = nullptr;
            }
            WindowComponent(WindowComponent &other) : clock()
            {
                window       = other.window;
                other.window = nullptr;
            }
            ~WindowComponent() override
            {
                if (window) window->close();
                delete window;
            };

            sf::RenderWindow           *window;
            [[maybe_unused]] ECS::Clock clock;
    };
} // namespace Engine::Components
