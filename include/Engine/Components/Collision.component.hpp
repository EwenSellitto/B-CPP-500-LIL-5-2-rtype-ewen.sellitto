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
#include "Engine/Components/Type.component.hpp"
#include "ECS/EventSubscriber.hpp"

namespace Engine::Components
{
    struct CollisionComponent : public ECS::BaseComponent {
        public:
            explicit CollisionComponent() {}

            ~CollisionComponent() override = default;
        private:
    };
} // namespace Engine::Components
