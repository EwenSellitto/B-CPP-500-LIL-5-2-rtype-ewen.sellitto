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
    struct EnemyAttackComponent : public ECS::BaseComponent {
        public:
            EnemyAttackComponent(size_t attackRate, size_t bulletType, sf::Vector2f bulletDestination,
                                 size_t bulletDuration)
                : lastAttack(0), attackRate(attackRate), bulletType(bulletType), bulletDestination(bulletDestination),
                  bulletDuration(bulletDuration)
            {
            }

            ~EnemyAttackComponent() override = default;

            std::vector<char> serialize(void) override
            {
                return std::vector<char>();
            }

            // last millisecond from epoch.
            size_t lastAttack;
            size_t attackRate;
            // bulletType needs to change.
            size_t bulletType;

            // these are the values to be passed to a MovingComponent.
            sf::Vector2f bulletDestination;
            size_t       bulletDuration;

        private:
    };
} // namespace Engine::Components
