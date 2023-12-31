/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct MissileComponent : public ECS::BaseComponent {
        public:
            MissileComponent() {}

            ~MissileComponent() override = default;


        private:
    };
} // namespace Engine::Components
