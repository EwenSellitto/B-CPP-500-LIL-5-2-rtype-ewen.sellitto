/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Position.compnent.hpp
*/

#pragma once

#include "ECS/Components.hpp"

namespace Engine::Components
{
    typedef std::pair<long int, long int> PositionComponent_serialized_t;

    struct PositionComponent : public ECS::BaseComponent {
        public:
            PositionComponent() : x(0), y(0){};
            explicit PositionComponent(int x, int y) : x(x), y(y){};
            ~PositionComponent() override = default;

            static PositionComponent_serialized_t serialize(PositionComponent &data)
            {
                return std::make_pair(data.x, data.y);
            }

            static PositionComponent deserialize(PositionComponent_serialized_t data)
            {
                return PositionComponent(data.first, data.second);
            }

            int x;
            int y;
    };
} // namespace Engine::Components
