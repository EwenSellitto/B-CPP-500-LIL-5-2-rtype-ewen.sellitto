/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Booster.component.hpp
*/

#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "ECS/Components.hpp"

namespace Rtype::Components
{
    struct BoosterComponent : ECS::BaseComponent {
        public:
            BoosterComponent() : duration_seconds(0){};
            BoosterComponent(int duration) : duration_seconds(duration){};
            ~BoosterComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&duration_seconds), sizeof(duration_seconds));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                BoosterComponent *boosterComponent;
                if (component == nullptr) {
                    boosterComponent = new BoosterComponent(0);
                } else {
                    boosterComponent = dynamic_cast<BoosterComponent *>(component);
                    if (boosterComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&boosterComponent->duration_seconds),
                         sizeof(boosterComponent->duration_seconds));

                return boosterComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::BoosterComponent;
            }

            int duration_seconds;
    };

    struct isBoosterComponent : ECS::BaseComponent {
        public:
            isBoosterComponent()           = default;
            ~isBoosterComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                isBoosterComponent *isBoosterComponent;
                if (component == nullptr) {
                    isBoosterComponent = new struct isBoosterComponent();
                } else {
                    isBoosterComponent = dynamic_cast<struct isBoosterComponent *>(component);
                    if (isBoosterComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                return isBoosterComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::isBoosterComponent;
            }
    };

} // namespace Rtype::Components
