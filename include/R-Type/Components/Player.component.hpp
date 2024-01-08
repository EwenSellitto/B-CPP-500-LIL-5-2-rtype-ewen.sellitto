/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <sstream>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct PlayerComponent : public ECS::BaseComponent {
        public:
            PlayerComponent()= default;

            ~PlayerComponent() override = default;

            std::vector<char> serialize() override
            {
                return {};
            }

            ECS::BaseComponent *deserialize(const std::vector<char> vec, ECS::BaseComponent *component) final
            {
                return nullptr;
            }

            ComponentType getType() override
            {
                return ComponentType::PlayerComponent;
            }

        private:
    };
} // namespace Engine::Components
