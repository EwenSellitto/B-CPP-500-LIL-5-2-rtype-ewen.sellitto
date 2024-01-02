/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct EnemyMovementsComponent : public ECS::BaseComponent {
        public:
            EnemyMovementsComponent(std::vector<std::pair<size_t, sf::Vector2f>> movementsQueueLoop)
                : movementsQueueLoop(movementsQueueLoop), currentMove(0)
            {
            }

            ~EnemyMovementsComponent() override = default;

            // these are the arguments to be passed to MovingComponent, they will be called each one after the other
            // in a loop.
            std::vector<std::pair<size_t, sf::Vector2f>> movementsQueueLoop;
            size_t                                       currentMove;

        private:
    };
} // namespace Engine::Components
