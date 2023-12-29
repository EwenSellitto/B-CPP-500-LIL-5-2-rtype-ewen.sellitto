/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Position.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct TypeComponent : public ECS::BaseComponent {
        public:
            typedef enum entityType {
                player,
                wall,
                missile,
                enemy
            } entityType_t;

            explicit TypeComponent(entityType_t type) : type(type){};
            ~TypeComponent() override = default;

            entityType_t type;
    };
} // namespace Engine::Components
