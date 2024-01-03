/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Position.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include <sstream>
#include <iostream>
#include <vector>

namespace Engine::Components
{
    typedef std::pair<long int, long int> PositionComponent_serialized_t;

    struct PositionComponent : public ECS::BaseComponent {
        public:
            PositionComponent() : x(0), y(0){};
            explicit PositionComponent(int x, int y) : x(x), y(y){};
            ~PositionComponent() override = default;

            std::vector<char> serialize(void) override
            {
                std::ostringstream oss(std::ios::binary);

                oss.write(reinterpret_cast<const char*>(&x), sizeof(int));
                oss.write(reinterpret_cast<const char*>(&y), sizeof(int));
                const std::string& str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(const std::vector<char>& vec, ECS::BaseComponent* component = nullptr)
            {
                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                if (component != nullptr) {
                    auto* enemyQueueComponent = dynamic_cast<PositionComponent*>(component);
                    if (enemyQueueComponent == nullptr) return nullptr;
                }
                while (iss.tellg() < vec.size()) {
                    PositionComponent_serialized_t data;
                    iss.read(reinterpret_cast<char*>(&data.first), sizeof(int));
                    iss.read(reinterpret_cast<char*>(&data.second), sizeof(int));
                    if (component == nullptr) {
                        component = new PositionComponent(data.first, data.second);
                    } else {
                        auto* positionComponent = dynamic_cast<PositionComponent*>(component);
                        if (positionComponent == nullptr) return nullptr;
                    }
                }
                return component;
            }

            int x;
            int y;
    };
} // namespace Engine::Components
