/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine
{

    namespace Components
    {
        typedef std::tuple<std::string, std::size_t, std::size_t, std::size_t, std::size_t, int, float, std::size_t,
                           std::size_t>
            Renderable_serialize_t;

        struct RenderableComponent : public ECS::BaseComponent {
            public:
                RenderableComponent()
                    : sprite(), size({0, 0}), position({0, 0}), priority(0), rotation(0), scale({1, 1}), _path(){};

                RenderableComponent(std::string texture_path, std::size_t pos_x, std::size_t pos_y, int priority,
                                    float rotation = 0, sf::Vector2<std::size_t> scale = {1, 1})
                    : texture(), sprite(), size(), position({pos_x, pos_y}), priority(priority), rotation(rotation),
                      scale(scale), _path(texture_path)
                {
                    setTexture(texture_path);
                };

                RenderableComponent(std::string texture_path, sf::Vector2<std::size_t> pos, int priority,
                                    float rotation = 0, sf::Vector2<std::size_t> scale = {1, 1})
                    : texture(), sprite(), size(), position(pos), priority(priority), rotation(rotation), scale(scale),
                      _path(texture_path)
                {
                    setTexture(texture_path);
                }

                ~RenderableComponent() = default;

                Renderable_serialize_t serialize() const
                {
                    return std::make_tuple(_path, position.x, position.y, size.x, size.y, priority, rotation, scale.x,
                                           scale.y);
                }

                static Renderable_serialize_t serialize(const RenderableComponent &r)
                {
                    return std::make_tuple(r._path, r.position.x, r.position.y, r.size.x, r.size.y, r.priority,
                                           r.rotation, r.scale.x, r.scale.y);
                }

                static RenderableComponent unserialise(Renderable_serialize_t data)
                {
                    return RenderableComponent(std::get<0>(data), std::get<1>(data), std::get<2>(data),
                                               std::get<5>(data), std::get<6>(data),
                                               {std::get<7>(data), std::get<8>(data)});
                }

                std::unique_ptr<sf::Texture> texture;
                sf::Sprite                   sprite;
                sf::Vector2<std::size_t>     size;
                sf::Vector2<std::size_t>     position;
                int                          priority;
                float                        rotation;
                sf::Vector2<std::size_t>     scale;

            private:
                std::string _path;

                void setTexture(std::string texture_path)
                {
                    texture->loadFromFile(texture_path);
                    sprite.setTexture(*texture);
                    sf::RenderWindow test = sf::RenderWindow();
                    test.draw(sprite);
                    size = {texture->getSize().x, texture->getSize().y};
                }
        };
    } // namespace Components
} // namespace Engine
