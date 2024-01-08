/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Dead.component.hpp
*/

#pragma once

#include <string>

#include "Engine/Components/Animation.component.hpp"

namespace Engine::Components
{

    class DeathAnimationComponent : public AnimationComponent
    {
        public:
            /*
             * @brief DeathAnimationComponent constructor
             * @param animationPath to the animation sprite.
             * @param x, y = offset from topLeft; ex: 32x32 texture which contains a maximum size of 5x18 in the middle,
             * its x, y after looking are : 13, 10
             * @param width, height; ex: the 5, 18 in question.
             * @param tileSize (tx, ty);      ex: the 32, 32 in question.
             * @param animationSpeed in ms.
             * @param frameCount = number of frame in the animation.
             */
            DeathAnimationComponent(std::string animationPath, int x, int y, int width, int height, int tx, int ty,
                                    int animationSpeed, int frameCount)
                : AnimationComponent(x, y, width, height, tx, ty, animationSpeed, frameCount),
                  animationPath(animationPath)
            {
            }

            ~DeathAnimationComponent() override = default;

            std::string animationPath;
    };
} // namespace Engine::Components
