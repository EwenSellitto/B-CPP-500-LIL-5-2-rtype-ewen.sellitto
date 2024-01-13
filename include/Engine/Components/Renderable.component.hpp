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
#include "R-Type/sprites.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct RenderableComponent : public ECS::BaseComponent {
        public:
            RenderableComponent()
                : sprite(), size({0, 0}), position({0, 0}), priority(0), rotation(0), scale({1, 1}), isDisplayed(false),
                  path()
            {
            }

            RenderableComponent(const std::string &texture_path, float pos_x, float pos_y, int priority,
                                float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false,
                                bool isDisplayed = true)
                : texture(), sprite(), size(), position({pos_x, pos_y}), priority(priority), rotation(rotation),
                  scale(scale), savedScale(scale), isDisplayed(isDisplayed), path(texture_path), setOrigin(setOrigin)

            {
                setTexture(texture_path);
            };

            RenderableComponent(const std::string &texture_path, sf::Vector2<float> pos, int priority,
                                float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false)
                : texture(), sprite(), size(), position(pos), priority(priority), rotation(rotation), scale(scale),
                  savedScale(scale), isDisplayed(true), path(texture_path), setOrigin(setOrigin)

            {
                setTexture(texture_path);
            }

            RenderableComponent(const std::string &spriteName, int priority = 0, sf::Vector2<float> scale = {1, 1},
                                int rotation = 270)
                : priority(priority), rotation(rotation), scale(scale), isDisplayed(true), name(spriteName)
            {
                auto it = spriteInfoMap.find(spriteName);
                if (it == spriteInfoMap.end()) throw std::runtime_error("Cannot find sprite " + spriteName);
                const SpriteInfo &info = it->second;
                setTexture(info.filePath);
                rotation = 270;
            }

            void reset(const std::string &texture_path, sf::Vector2<float> pos, int priority, float rotation = 0,
                       sf::Vector2<float> scale = {1, 1}, bool setOrigin = false, bool isDisplayed = true)
            {
                this->position    = pos;
                this->priority    = priority;
                this->rotation    = rotation;
                this->scale       = scale;
                this->path        = texture_path;
                this->setOrigin   = setOrigin;
                this->isDisplayed = isDisplayed;

                setTexture(texture_path);
            }

            ~RenderableComponent() override = default;

            sf::Texture              texture;
            sf::Sprite               sprite;
            sf::Vector2<std::size_t> size;
            sf::Vector2<float>       position;
            int                      priority;
            float                    rotation;
            sf::Vector2<float>       scale;
            sf::Vector2<float>       savedScale;
            bool                     isDisplayed;
            std::string              path;
            bool                     setOrigin = false;
            std::string              name;

        private:
            void setTexture(const std::string &texture_path)
            {
                if (!texture.loadFromFile(texture_path))
                    throw std::runtime_error("Cannot load texture " + texture_path);
                sprite = sf::Sprite(texture);
                sprite.setPosition(position.x, position.y);
                sprite.setRotation(rotation);
                size = {texture.getSize().x, texture.getSize().y};
                if (setOrigin) sprite.setOrigin(static_cast<float>(size.x) / 2, static_cast<float>(size.y) / 2);
            }
    };
} // namespace Engine::Components
