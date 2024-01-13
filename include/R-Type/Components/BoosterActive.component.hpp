/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** BoosterActive.component.hpp
*/

#pragma once

#include <iostream>
#include <vector>

#include "ECS/Components.hpp"
#include "SFML/System/Clock.hpp"

namespace Rtype::Components
{
    struct BoosterActiveComponent : ECS::BaseComponent {
        public:
            BoosterActiveComponent() : duration(0), clock({}) {}
            BoosterActiveComponent(int duration) : duration(duration), clock({}) {}
            ~BoosterActiveComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&duration), sizeof(duration));
                oss.write(reinterpret_cast<const char *>(&hitpoints), sizeof(hitpoints));
                oss.write(reinterpret_cast<const char *>(&clock), sizeof(clock));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                BoosterActiveComponent *boosterActiveComponent;
                if (component == nullptr) {
                    boosterActiveComponent = new BoosterActiveComponent(0);
                } else {
                    boosterActiveComponent = dynamic_cast<BoosterActiveComponent *>(component);
                    if (boosterActiveComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&boosterActiveComponent->duration),
                         sizeof(boosterActiveComponent->duration));
                iss.read(reinterpret_cast<char *>(&boosterActiveComponent->hitpoints),
                         sizeof(boosterActiveComponent->hitpoints));
                iss.read(reinterpret_cast<char *>(&boosterActiveComponent->clock),
                         sizeof(boosterActiveComponent->clock));

                return boosterActiveComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::BoosterActiveComponent;
            }

            int       duration;
            int       hitpoints = 3;
            sf::Clock clock;
    };

} // namespace Rtype::Components
