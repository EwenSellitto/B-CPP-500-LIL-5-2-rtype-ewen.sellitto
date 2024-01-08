/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "Engine/Engine.hpp"

namespace Engine::Components
{
    struct BaseBulletComponent : public ECS::BaseComponent {
        public:
            explicit BaseBulletComponent(bool fromEnemy, std::size_t x_destroy = DEFAULT_WINDOW_SIZE_X + 200,
                                         std::size_t y_destroy = DEFAULT_WINDOW_SIZE_Y + 200)
                : fromEnemy(fromEnemy), x_destroy(x_destroy)
            {
            }
            ~BaseBulletComponent() override = default;

            bool        fromEnemy;
            std::size_t x_destroy;
            std::size_t y_destroy;

        private:
    };
} // namespace Engine::Components
