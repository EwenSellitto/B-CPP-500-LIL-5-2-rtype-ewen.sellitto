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
    struct EnemyQueueComponent : public ECS::BaseComponent {
        public:
            EnemyQueueComponent() {}
            EnemyQueueComponent(
                std::vector<
                    std::pair<bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t(float, bool)>>>>
                    enemyQueueFactories)
                : enemyQueueFactories(enemyQueueFactories)
            {
            }

            ~EnemyQueueComponent() override = default;

            // the pair consists of a bool, and data about the enemy to spawn
            // the bool is either the enemy has already spawned or not, should default to true.

            // size_t is the x where when map progress has attained it spawns.
            // float, is the y position
            // bool is 'isAttacking' because not every enemy attacks.
            // ==> but they will all attack the same. (within definition in the function.)
            // then you need to call the std::function with the two floats and the bool.
            std::vector<std::pair<bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t(float, bool)>>>>
                enemyQueueFactories;

        private:
    };
} // namespace Engine::Components
