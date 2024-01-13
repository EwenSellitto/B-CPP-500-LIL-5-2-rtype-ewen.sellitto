/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct MissileComponent : public ECS::BaseComponent {
        public:
            MissileComponent() = default;

            ~MissileComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                MissileComponent *missileComponent;
                if (component == nullptr) {
                    missileComponent = new MissileComponent();
                } else {
                    missileComponent = dynamic_cast<MissileComponent *>(component);
                    if (missileComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                return missileComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::MissileComponent;
            }

        private:
    };
} // namespace Engine::Components
