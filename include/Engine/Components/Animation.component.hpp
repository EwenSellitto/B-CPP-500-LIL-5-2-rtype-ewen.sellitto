/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>

#include "ECS/Components.hpp"
#include "R-Type/sprites.hpp"

namespace Engine::Components
{
    struct AnimationComponent : ECS::BaseComponent {
        public:
            AnimationComponent() = default;
            /*
             * @brief AnimationComponent constructor
             * @param x, y = offset from topLeft; ex: 32x32 texture which contains a maximum size of 5x18 in the middle,
             * its x, y after looking are : 13, 10
             * @param width, height; ex: the 5, 18 in question.
             * @param tileSize (tx, ty);      ex: the 32, 32 in question.
             * @param animationSpeed in ms.
             * @param frameCount = number of frame in the animation.
             */
            AnimationComponent(int x, int y, int width, int height, int tx, int ty, int animationSpeed, int frameCount)
                : textureRect(x, y, width, height), tileSize(tx, ty), animationSpeed(animationSpeed),
                  frameCount(frameCount){};
            // AnimationComponent(const std::string &spriteName): name(spriteName) {
            //     auto it = spriteInfoMap.find(spriteName);
            //     if (it != spriteInfoMap.end()) {
            //         const SpriteInfo& info = it->second;
            //         textureRect = sf::Rect<int>(info.offsetX, info.offsetY, info.width, info.height);
            //         tileSize = sf::Vector2i(info.oneframeX, info.oneframeY);
            //         animationSpeed = info.animationSpeed;
            //         frameCount = info.nbFrames;
            //     } else {
            //         // Handle error if spriteName is not found in spriteInfoMap
            //     }
            // }

            ~AnimationComponent() = default;

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
            std::string   name;
            sf::Clock     clock{};
    };
} // namespace Engine::Components
