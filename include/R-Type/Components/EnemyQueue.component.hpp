/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "ECS/Components.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct EnemyQueueComponent : public ECS::BaseComponent {
        public:
            EnemyQueueComponent() = default;

            explicit EnemyQueueComponent(
                std::vector<std::pair<
                    bool,
                    std::pair<std::tuple<size_t, float, bool, std::vector<std::pair<size_t, sf::Vector2f>>>, size_t>>>
                    newEnemyQueueFactories)
                : newEnemyQueueFactories(newEnemyQueueFactories)
            {
            }

            ~EnemyQueueComponent() override = default;

            // Sérialisation pour newEnemyQueueFactories
            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                size_t             size = newEnemyQueueFactories.size();
                oss.write(reinterpret_cast<const char *>(&size), sizeof(size));

                for (const auto &item : newEnemyQueueFactories) {
                    // Sérialiser le bool
                    bool hasSpawned = item.first;
                    oss.write(reinterpret_cast<const char *>(&hasSpawned), sizeof(hasSpawned));

                    // Sérialiser les données du tuple
                    auto &[x, y, isAttacking, positions] = item.second.first;
                    oss.write(reinterpret_cast<const char *>(&x), sizeof(x));
                    oss.write(reinterpret_cast<const char *>(&y), sizeof(y));
                    oss.write(reinterpret_cast<const char *>(&isAttacking), sizeof(isAttacking));

                    size_t positionsSize = positions.size();
                    oss.write(reinterpret_cast<const char *>(&positionsSize), sizeof(positionsSize));
                    for (const auto &pos : positions) {
                        size_t       posId    = pos.first;
                        sf::Vector2f posValue = pos.second;
                        oss.write(reinterpret_cast<const char *>(&posId), sizeof(posId));
                        oss.write(reinterpret_cast<const char *>(&posValue), sizeof(posValue));
                    }

                    // Sérialiser le size_t (factoryId)
                    size_t factoryId = item.second.second;
                    oss.write(reinterpret_cast<const char *>(&factoryId), sizeof(factoryId));
                }

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) override
            {
                EnemyQueueComponent *enemyQueueComponent;
                if (component == nullptr) {
                    enemyQueueComponent = new EnemyQueueComponent();
                } else {
                    enemyQueueComponent = dynamic_cast<EnemyQueueComponent *>(component);
                    if (enemyQueueComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                size_t size;
                iss.read(reinterpret_cast<char *>(&size), sizeof(size));

                newEnemyQueueFactories.clear();
                for (size_t i = 0; i < size; ++i) {
                    bool hasSpawned;
                    iss.read(reinterpret_cast<char *>(&hasSpawned), sizeof(hasSpawned));

                    size_t x;
                    float  y;
                    bool   isAttacking;
                    iss.read(reinterpret_cast<char *>(&x), sizeof(x));
                    iss.read(reinterpret_cast<char *>(&y), sizeof(y));
                    iss.read(reinterpret_cast<char *>(&isAttacking), sizeof(isAttacking));

                    size_t positionsSize;
                    iss.read(reinterpret_cast<char *>(&positionsSize), sizeof(positionsSize));
                    std::vector<std::pair<size_t, sf::Vector2f>> positions;
                    for (size_t j = 0; j < positionsSize; ++j) {
                        size_t       posId;
                        sf::Vector2f posValue;
                        iss.read(reinterpret_cast<char *>(&posId), sizeof(posId));
                        iss.read(reinterpret_cast<char *>(&posValue), sizeof(posValue));
                        positions.emplace_back(posId, posValue);
                    }

                    size_t factoryId;
                    iss.read(reinterpret_cast<char *>(&factoryId), sizeof(factoryId));

                    newEnemyQueueFactories.emplace_back(
                        hasSpawned, std::make_pair(std::make_tuple(x, y, isAttacking, positions), factoryId));
                }
                return enemyQueueComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::EnemyQueueComponent;
            }

            // the pair consists of a bool, and data about the enemy to spawn
            // the bool is either the enemy has already spawned or not, should default to true.

            // size_t is the x where when map progress has attained it spawns.
            // float, is the y position
            // bool is 'isAttacking' because not every enemy attacks.
            // ==> but they will all attack the same. (within definition in the function.)
            // then you need to call the std::function with the two floats and the bool.

            std::vector<std::pair<
                bool, std::pair<std::tuple<size_t, float, bool, std::vector<std::pair<size_t, sf::Vector2f>>>, size_t>>>
                newEnemyQueueFactories = {};

        private:
    };
} // namespace Engine::Components
