/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"

namespace Engine::Components
{
    struct AnimationComponent {
        public:
            AnimationComponent() = default;
            AnimationComponent(int x, int y, int width, int height, int animationSpeed)
                : textureRect(x, y, width, height), animationSpeed(animationSpeed){};
            ~AnimationComponent() = default;

            sf::Rect<int> textureRect = {0, 0, 0, 0};
            int           frame{0};
            int           frameCount{0};
            sf::Clock     clock{};
            int           animationSpeed{0}; // miliseconds
    };
} // namespace Engine::Components
