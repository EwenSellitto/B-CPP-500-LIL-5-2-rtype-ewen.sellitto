/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** ExcludeCollision.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
namespace Engine::Components
{
    class ExcludeCollisionComponent : public ECS::BaseComponent
    {
        public:
            ExcludeCollisionComponent(std::size_t id) : id(id) {}
            ~ExcludeCollisionComponent() override = default;

            std::vector<char> serialize(void) override
            {
                return std::vector<char>();
            }

            std::size_t id;
    };
} // namespace Engine::Components
