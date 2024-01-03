/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "ECS/Components.hpp"
#include "ECS/Entity.hpp"
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

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                for (const auto &item : enemyQueueFactories) {
                    // Sérialiser le premier booléen
                    const bool &hasSpawned = item.first;
                    oss.write(reinterpret_cast<const char *>(&hasSpawned), sizeof(bool));

                    // Sérialiser les données du tuple
                    const auto &[x, y, isAttacking] = item.second.first;
                    oss.write(reinterpret_cast<const char *>(&x), sizeof(size_t));
                    oss.write(reinterpret_cast<const char *>(&y), sizeof(float));
                    oss.write(reinterpret_cast<const char *>(&isAttacking), sizeof(bool));

                    // Sérialiser les données retournées par la std::function
                    // std::vector<size_t> functionData = item.second.second(y, isAttacking);
                    // size_t functionDataSize = functionData.size();
                    // oss.write(reinterpret_cast<const char*>(&functionDataSize), sizeof(size_t));
                    // for (const auto& data : functionData) {
                    //     oss.write(reinterpret_cast<const char*>(&data), sizeof(size_t));
                    // }
                }
                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(const std::vector<char> &vec,
                                                   ECS::BaseComponent      *component = nullptr)
            {
                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                if (component != nullptr) {
                    auto *enemyQueueComponent = dynamic_cast<EnemyQueueComponent *>(component);
                    if (enemyQueueComponent == nullptr) return nullptr;
                }
                while (iss.tellg() < vec.size()) {
                    // Désérialiser le premier booléen
                    bool hasSpawned;
                    iss.read(reinterpret_cast<char *>(&hasSpawned), sizeof(bool));

                    // Désérialiser les données du tuple
                    size_t x;
                    float  y;
                    bool   isAttacking;
                    iss.read(reinterpret_cast<char *>(&x), sizeof(size_t));
                    iss.read(reinterpret_cast<char *>(&y), sizeof(float));
                    iss.read(reinterpret_cast<char *>(&isAttacking), sizeof(bool));

                    // Désérialiser les données retournées par la std::function
                    // size_t functionDataSize;
                    // iss.read(reinterpret_cast<char*>(&functionDataSize), sizeof(size_t));
                    // std::vector<size_t> functionData(functionDataSize);
                    // for (size_t& data : functionData) {
                    //     iss.read(reinterpret_cast<char*>(&data), sizeof(size_t));
                    // }

                    // Ajouter l'élément reconstruit à enemyQueueFactories
                    // Note: Ici, vous devez remplacer std::function par une fonction valide

                    if (component == nullptr) {
                        component = new EnemyQueueComponent(
                            std::vector<std::pair<
                                bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t(float, bool)>>>>(
                                {std::make_pair(hasSpawned, std::make_pair(std::make_tuple(x, y, isAttacking),
                                                                           std::function<size_t(float, bool)>()))}));
                    } else {
                        EnemyQueueComponent *enemyQueueComponent = dynamic_cast<EnemyQueueComponent *>(component);
                        if (enemyQueueComponent == nullptr) return nullptr;
                        enemyQueueComponent->enemyQueueFactories.push_back(
                            std::make_pair(hasSpawned, std::make_pair(std::make_tuple(x, y, isAttacking),
                                                                      std::function<size_t(float, bool)>())));
                    }
                }
                return component;
            }

            // the pair consists of a bool, and data about the enemy to spawn
            // the bool is either the enemy has already spawned or not, should default to true.

            // size_t is the x where when map progress has attained it spawns.
            // float, is the y position
            // bool is 'isAttacking' because not every enemy attacks.
            // ==> but they will all attack the same. (within definition in the function.)
            // then you need to call the std::function with the two floats and the bool.
            std::vector<std::pair<bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t(float, bool)>>>>
                enemyQueueFactories = {};
    };
} // namespace Engine::Components
