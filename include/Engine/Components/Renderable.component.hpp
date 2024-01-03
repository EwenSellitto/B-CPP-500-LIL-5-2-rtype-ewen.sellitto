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
    struct RenderableComponent : public ECS::BaseComponent {
        public:
            RenderableComponent()
                : sprite(), size({0, 0}), position({0, 0}), priority(0), rotation(0), scale({1, 1}), isDisplayed(false),
                  path()
            {
            }

            RenderableComponent(const std::string &texture_path, float pos_x, float pos_y, int priority,
                                float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false)
                : texture(), sprite(), size(), position({pos_x, pos_y}), priority(priority), rotation(rotation),
                  scale(scale), isDisplayed(true), path(texture_path), setOrigin(setOrigin)

            {
                setTexture(texture_path);
            };

            RenderableComponent(const std::string &texture_path, sf::Vector2<float> pos, int priority,
                                float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false)
                : texture(), sprite(), size(), position(pos), priority(priority), rotation(rotation), scale(scale),
                  isDisplayed(true), path(texture_path), setOrigin(setOrigin)

            {
                setTexture(texture_path);
            }

            ~RenderableComponent() override = default;

            std::vector<char> serialize(void) override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&position.x), sizeof(position.x));
                oss.write(reinterpret_cast<const char *>(&position.y), sizeof(position.y));
                oss.write(reinterpret_cast<const char *>(&priority), sizeof(priority));
                oss.write(reinterpret_cast<const char *>(&rotation), sizeof(rotation));
                oss.write(reinterpret_cast<const char *>(&scale.x), sizeof(scale.x));
                oss.write(reinterpret_cast<const char *>(&scale.y), sizeof(scale.y));
                oss.write(reinterpret_cast<const char *>(&isDisplayed), sizeof(isDisplayed));

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr)
            {
                RenderableComponent *renderableComponent;
                if (component == nullptr) {
                    renderableComponent = new RenderableComponent();
                } else {
                    renderableComponent = dynamic_cast<RenderableComponent *>(component);
                    if (renderableComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&renderableComponent->position.x),
                         sizeof(renderableComponent->position.x));
                iss.read(reinterpret_cast<char *>(&renderableComponent->position.y),
                         sizeof(renderableComponent->position.y));
                iss.read(reinterpret_cast<char *>(&renderableComponent->priority),
                         sizeof(renderableComponent->priority));
                iss.read(reinterpret_cast<char *>(&renderableComponent->rotation),
                         sizeof(renderableComponent->rotation));
                iss.read(reinterpret_cast<char *>(&renderableComponent->scale.x), sizeof(renderableComponent->scale.x));
                iss.read(reinterpret_cast<char *>(&renderableComponent->scale.y), sizeof(renderableComponent->scale.y));
                iss.read(reinterpret_cast<char *>(&renderableComponent->isDisplayed),
                         sizeof(renderableComponent->isDisplayed));
                // Ici, il faut configurer la texture et le sprite en utilisant 'path'

                return renderableComponent;
            }

            sf::Texture              texture;
            sf::Sprite               sprite;
            sf::Vector2<std::size_t> size;
            sf::Vector2<float>       position;
            int                      priority;
            float                    rotation;
            sf::Vector2<float>       scale;
            bool                     isDisplayed;
            std::string              path;
            bool                     setOrigin = false;

        private:
            void setTexture(const std::string &texture_path)
            {
                if (!texture.loadFromFile(texture_path))
                    throw std::runtime_error("Cannot load texture " + texture_path);
                sprite = sf::Sprite(texture);
                sprite.setScale(scale.x, scale.y);
                sprite.setPosition(position.x, position.y);
                sprite.setRotation(rotation);
                size = {texture.getSize().x, texture.getSize().y};
                if (setOrigin) sprite.setOrigin(size.x / 2, size.y / 2);
            }
    };
} // namespace Engine::Components
