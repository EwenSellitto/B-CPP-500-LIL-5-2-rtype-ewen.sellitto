/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct RenderableComponent : public ECS::BaseComponent {
        public:
            RenderableComponent()
                : sprite(), size({0, 0}), layer(0), rotation(0), scale({1, 1}), isDisplayed(false), path(){};

            RenderableComponent(const std::string &texture_path, int priority, float rotation = 0,
                                sf::Vector2<float> scale = {1, 1})
                : texture(), sprite(), size(), layer(priority), rotation(rotation), scale(scale), isDisplayed(true),
                  path(texture_path)

            {
                if (!texture.loadFromFile(texture_path))
                    throw std::runtime_error("Cannot load texture " + texture_path);
                sprite = sf::Sprite(texture);
                sprite.setScale(scale.x, scale.y);
                size = {texture.getSize().x, texture.getSize().y};
            };

            ~RenderableComponent() override = default;

            sf::Texture              texture;
            sf::Sprite               sprite;
            sf::Vector2<std::size_t> size;
            int                      layer;
            float                    rotation;
            sf::Vector2<float>       scale;
            bool                     isDisplayed;
            std::string              path;
    };
} // namespace Engine::Components
