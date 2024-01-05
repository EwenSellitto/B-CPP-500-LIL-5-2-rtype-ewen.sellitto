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
    struct MissileComponent : public ECS::BaseComponent {
        public:
            MissileComponent() {}

            ~MissileComponent() override = default;

            std::vector<char> serialize(void) override
            {
                return std::vector<char>();
            }

        private:
    };
} // namespace Engine::Components
