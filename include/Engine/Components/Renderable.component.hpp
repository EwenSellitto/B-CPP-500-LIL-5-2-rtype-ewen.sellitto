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
#include <sstream>
#include <tuple>
#include <vector>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "public/ComponentsType.hpp"

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
                setTexture();
            };

            RenderableComponent(const std::string &texture_path, sf::Vector2<float> pos, int priority,
                                float rotation = 0, sf::Vector2<float> scale = {1, 1}, bool setOrigin = false)
                : texture(), sprite(), size(), position(pos), priority(priority), rotation(rotation), scale(scale),
                  isDisplayed(true), path(texture_path), setOrigin(setOrigin)

            {
                setTexture();
            }

            void setTexture()
            {
                if (!texture.loadFromFile(path)) throw std::runtime_error("Cannot load texture " + path);
                sprite = sf::Sprite(texture);
                sprite.setScale(scale.x, scale.y);
                sprite.setPosition(position.x, position.y);
                sprite.setRotation(rotation);
                size = {texture.getSize().x, texture.getSize().y};
                if (setOrigin) sprite.setOrigin(size.x / 2, size.y / 2);
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
                oss.write(reinterpret_cast<const char *>(&size.x), sizeof(size.x));
                oss.write(reinterpret_cast<const char *>(&size.y), sizeof(size.y));
                oss.write(reinterpret_cast<const char *>(&isDisplayed), sizeof(isDisplayed));

                size_t pathLength = path.length();
                oss.write(reinterpret_cast<const char *>(&pathLength), sizeof(pathLength));
                oss.write(path.c_str(), pathLength);

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
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
                iss.read(reinterpret_cast<char *>(&renderableComponent->size.x), sizeof(renderableComponent->size.x));
                iss.read(reinterpret_cast<char *>(&renderableComponent->size.y), sizeof(renderableComponent->size.y));
                iss.read(reinterpret_cast<char *>(&renderableComponent->isDisplayed),
                         sizeof(renderableComponent->isDisplayed));

                // Désérialisation de la chaîne 'path'
                size_t pathLength;
                iss.read(reinterpret_cast<char *>(&pathLength), sizeof(pathLength));
                std::string spritePath(pathLength, '\0');
                iss.read(&spritePath[0], pathLength);
                renderableComponent->path = spritePath;

                return renderableComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::RenderableComponent;
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
    };
} // namespace Engine::Components
