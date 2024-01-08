/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <string>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Rect.hpp"

namespace Engine::Components
{
    struct CollisionComponent : public ECS::BaseComponent {
        public:
            explicit CollisionComponent(float off_x = 0, float off_y = 0, float size_x = 0, float size_y = 0)
                : rect(off_x, off_y, size_x, size_y)
            {
            }

            ~CollisionComponent() override = default;

            sf::FloatRect rect;
    };
} // namespace Engine::Components
