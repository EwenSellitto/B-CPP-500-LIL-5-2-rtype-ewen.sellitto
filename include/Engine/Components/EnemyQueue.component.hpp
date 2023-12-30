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
    struct EnemyQueueComponent : public ECS::BaseComponent {
        public:
            EnemyQueueComponent() {}
            EnemyQueueComponent(
                std::vector<std::pair<std::tuple<size_t, float, bool>, std::function<void(float, bool)>>>
                    enemyQueueFactories) : enemyQueueFactories(enemyQueueFactories)
            {
            }

            ~EnemyQueueComponent() override = default;

            // size_t is the x where when map progress has attained it spawns.
            // float, is the y position
            // bool is 'isAttacking' because not every enemy attacks.
            // ==> but they will all attack the same. (within definition in the function.)
            // then you need to call the std::function with the two floats and the bool.
            std::vector<std::pair<std::tuple<size_t, float, bool>, std::function<void(float, bool)>>>
                enemyQueueFactories;
        private:
    };
} // namespace Engine::Components
