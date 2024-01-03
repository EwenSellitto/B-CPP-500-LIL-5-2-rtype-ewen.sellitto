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

            std::vector<char> serialize(void) override {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char*>(&x), sizeof(x));
                oss.write(reinterpret_cast<const char*>(&y), sizeof(y));

                const std::string& str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr) {
                PositionComponent* positionComponent;
                if (component == nullptr) {
                    positionComponent = new PositionComponent();
                } else {
                    positionComponent = dynamic_cast<PositionComponent*>(component);
                    if (positionComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char*>(&positionComponent->x), sizeof(positionComponent->x));
                iss.read(reinterpret_cast<char*>(&positionComponent->y), sizeof(positionComponent->y));

                return positionComponent;
            }

            int x;
            int y;
    };
} // namespace Engine::Components
