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
    struct MovingComponent : public ECS::BaseComponent {
        public:
            MovingComponent(sf::Vector2f initialPos, size_t moveDuration,
                            sf::Vector2f moveAmount)
                : initialPos(initialPos), moveAmount(moveAmount), moveDuration(moveDuration)
            {
                if (moveDuration == 0)
                    this->moveDuration = 1;
                auto now = std::chrono::high_resolution_clock::now();
                auto epoch = now.time_since_epoch();
                moveStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
            }

            ~MovingComponent() override = default;

            size_t moveStartTime;
            sf::Vector2f initialPos;
            sf::Vector2f moveAmount;
            size_t moveDuration;

        private:
    };
} // namespace Engine::Components
