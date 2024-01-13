/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Health.component.hpp
*/

#pragma once

#include <sstream>

#include "ECS/Components.hpp"

namespace Rtype::Components
{
    struct HealthComponent : ECS::BaseComponent {
        public:
            HealthComponent() : health(0) {}
            HealthComponent(int health) : health(health) {}
            ~HealthComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&health), sizeof(health));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize([[maybe_unused]] const std::vector<char> vec,
                                            [[maybe_unused]] ECS::BaseComponent     *component) final
            {
                HealthComponent *healthComponent;
                if (component == nullptr) {
                    healthComponent = new HealthComponent();
                } else {
                    healthComponent = dynamic_cast<HealthComponent *>(component);
                    if (healthComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&healthComponent->health), sizeof(healthComponent->health));

                return healthComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::HealthComponent;
            }

            int health;
    };
} // namespace Rtype::Components
