/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <sstream>

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

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&lastAttack), sizeof(lastAttack));
                oss.write(reinterpret_cast<const char *>(&attackRate), sizeof(attackRate));
                oss.write(reinterpret_cast<const char *>(&bulletType), sizeof(bulletType));
                oss.write(reinterpret_cast<const char *>(&bulletDestination.x), sizeof(bulletDestination.x));
                oss.write(reinterpret_cast<const char *>(&bulletDestination.y), sizeof(bulletDestination.y));
                oss.write(reinterpret_cast<const char *>(&bulletDuration), sizeof(bulletDuration));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr)
            {
                EnemyAttackComponent *enemyAttack;
                if (component == nullptr) {
                    enemyAttack = new EnemyAttackComponent(0, 0, sf::Vector2f(0, 0), 0);
                } else {
                    enemyAttack = dynamic_cast<EnemyAttackComponent *>(component);
                    if (enemyAttack == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&enemyAttack->lastAttack), sizeof(enemyAttack->lastAttack));
                iss.read(reinterpret_cast<char *>(&enemyAttack->attackRate), sizeof(enemyAttack->attackRate));
                iss.read(reinterpret_cast<char *>(&enemyAttack->bulletType), sizeof(enemyAttack->bulletType));
                iss.read(reinterpret_cast<char *>(&enemyAttack->bulletDestination.x),
                         sizeof(enemyAttack->bulletDestination.x));
                iss.read(reinterpret_cast<char *>(&enemyAttack->bulletDestination.y),
                         sizeof(enemyAttack->bulletDestination.y));
                iss.read(reinterpret_cast<char *>(&enemyAttack->bulletDuration), sizeof(enemyAttack->bulletDuration));

                return enemyAttack;
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
