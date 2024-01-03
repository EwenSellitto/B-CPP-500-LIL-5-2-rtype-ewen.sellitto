/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

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

            std::vector<char> serialize(void) override
            {
                return std::vector<char>();
            }

            // x, y = offset from topLeft; ex: 32x32 texture which contains a maximum size of 5x18 in the middle,
            //                   its x, y after looking are : 13, 10
            // width, height; ex: the 5, 18 in question.
            // tileSize (tx, ty);      ex: the 32, 32 in question.
            // animationSpeed in ms;
            sf::Rect<int> textureRect = {0, 0, 0, 0};
            sf::Vector2i  tileSize    = {0, 0};
            int           frame{0};
            int           animationSpeed{0};
            int           frameCount{0};
            sf::Clock     clock{};
    };
} // namespace Engine::Components
