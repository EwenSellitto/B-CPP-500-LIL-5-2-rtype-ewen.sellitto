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
    struct BulletComponent : public ECS::BaseComponent {
        public:
            BulletComponent(float damage, float speed, float direction)
                : _damage(damage), _speed(speed), _direction(direction){};

            ~BulletComponent() override = default;

        private:
            int _damage    = 10;
            int _speed     = 10;
            int _direction = 1;
    };
} // namespace Engine::Components
