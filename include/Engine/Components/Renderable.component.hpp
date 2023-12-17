/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine
{

    namespace Components
    {
        typedef std::tuple<std::string, std::size_t, std::size_t, std::size_t, std::size_t, int> Renderable_serialize_t;

        struct Renderable : public ECS::BaseComponent {
            public:
                Renderable() : sprite(), size({0, 0}), position({0, 0}), priority(0), _path(){};
                Renderable(std::string texture_path, std::size_t pos_x, std::size_t pos_y, int priority)
                    : texture(), sprite(), size(), position({pos_x, pos_y}), priority(priority), _path(texture_path)
                {
                    setTexture(texture_path);
                };
                Renderable(std::string texture_path, sf::Vector2<std::size_t> pos, int priority)
                    : texture(), sprite(), size(), position(pos), priority(priority), _path(texture_path)
                {
                    setTexture(texture_path);
                }

                ~Renderable() = default;

                Renderable_serialize_t serialize() const
                {
                    return std::make_tuple(_path, position.x, position.y, size.x, size.y, priority);
                }

                static Renderable_serialize_t serialize(const Renderable &r)
                {
                    return std::make_tuple(r._path, r.position.x, r.position.y, r.size.x, r.size.y, r.priority);
                }

                static Renderable unserialise(Renderable_serialize_t data)
                {
                    return Renderable(std::get<0>(data), std::get<1>(data), std::get<2>(data), std::get<5>(data));
                }

                std::unique_ptr<sf::Texture> texture;
                sf::Sprite                   sprite;
                sf::Vector2<std::size_t>     size;
                sf::Vector2<std::size_t>     position;
                int                          priority;

            private:
                std::string _path;

                void setTexture(std::string texture_path)
                {
                    texture->loadFromFile(texture_path);
                    sprite.setTexture(*texture);
                    size = {texture->getSize().x, texture->getSize().y};
                }
        };
    } // namespace Components
} // namespace Engine
