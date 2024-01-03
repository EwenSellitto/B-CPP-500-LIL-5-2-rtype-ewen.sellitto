/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct WorldMoveProgressComponent : public ECS::BaseComponent {
        public:
            WorldMoveProgressComponent() : progress(0) {}
            WorldMoveProgressComponent(size_t startingTime, size_t progress, size_t speed)
                : startingTime(startingTime), progress(progress), speed(speed)
            {
            }

            ~WorldMoveProgressComponent() override = default;

            std::vector<char> serialize(void) override
            {
                return std::vector<char>();
            }

            // in epoch milliseconds
            size_t startingTime;

            // this is the progress of the world in the x-axis,
            // the walls, enemies are spawning because of it.
            size_t progress;
            // speed in +x per second.
            size_t speed;

        private:
    };
} // namespace Engine::Components
