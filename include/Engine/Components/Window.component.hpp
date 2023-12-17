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

class ScreenComponent : public ECS::BaseComponent
{
    public:
        ScreenComponent() : _window(sf::RenderWindow(sf::VideoMode(1920, 1080), "Default")), _clock(){};
        ScreenComponent(unsigned int size_x, unsigned int size_y, std::string title)
            : _window(sf::RenderWindow(sf::VideoMode(size_x, size_y), title)), _clock(){};
        ScreenComponent(sf::VideoMode mode, std::string title = "Default")
            : _window(sf::VideoMode(mode), title), _clock(){};
        ~ScreenComponent() override
        {
            _window.close();
        };

    private:
        sf::RenderWindow            _window;
        [[maybe_unused]] ECS::Clock _clock;
};
