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
    struct ViewComponent : public ECS::BaseComponent {
        public:
            ViewComponent()
                : position(), view()
            {
                view.setCenter(sf::Vector2f(400, 300));
                view.setSize(sf::Vector2f(800, 600));
            }

            ViewComponent(sf::Vector2<float> position, sf::Vector2<float> size)
                : position(position), view()
            {
                view.setCenter(sf::Vector2f(position.x, position.y));
                view.setSize(sf::Vector2f(size.x, size.y));
            }

            ~ViewComponent() override = default;

            sf::Vector2<float> position;
            sf::View view;

        private:
    };
} // namespace Engine::Components
