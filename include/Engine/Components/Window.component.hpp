/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Screen.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "ECS/Clock.hpp"
#include "ECS/Components.hpp"

class WindowComponent : public ECS::BaseComponent
{
    public:
        WindowComponent() : window(sf::RenderWindow(sf::VideoMode(1920, 1080), "Default")), clock(){};
        WindowComponent(unsigned int size_x, unsigned int size_y, std::string title)
            : window(sf::RenderWindow(sf::VideoMode(size_x, size_y), title)), clock(){};
        WindowComponent(sf::VideoMode mode, std::string title = "Default") : window(mode, title), clock(){};
        ~WindowComponent() override
        {
            window.close();
        };

        sf::RenderWindow            window;
        [[maybe_unused]] ECS::Clock clock;
};
