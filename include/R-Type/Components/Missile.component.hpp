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
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct MissileComponent : public ECS::BaseComponent {
        public:
            MissileComponent() = default;

            ~MissileComponent() override = default;

            std::vector<char> serialize() override
            {
                return {};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                return nullptr;
            }

            ComponentType getType() override
            {
                return ComponentType::MissileComponent;
            }

        private:
    };
} // namespace Engine::Components
