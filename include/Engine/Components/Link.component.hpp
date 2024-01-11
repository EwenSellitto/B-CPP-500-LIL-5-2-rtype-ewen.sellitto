/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Link.component.hpp
*/

#pragma once

#include <cstddef>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct LinkComponent : ECS::BaseComponent {
            LinkComponent(std::size_t id) : entity(id) {}
            ~LinkComponent() override = default;
            std::size_t entity;
    };
} // namespace Engine::Components
