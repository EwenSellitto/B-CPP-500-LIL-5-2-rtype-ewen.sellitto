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
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct EnemyMovementsComponent : public ECS::BaseComponent {
        public:
            EnemyMovementsComponent() : movementsQueueLoop({}), currentMove(0) {}
            EnemyMovementsComponent(std::vector<std::pair<size_t, sf::Vector2f>> movementsQueueLoop)
                : movementsQueueLoop(movementsQueueLoop), currentMove(0)
            {
            }

            ~EnemyMovementsComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&currentMove), sizeof(size_t));
                for (const auto &item : movementsQueueLoop) {
                    // Sérialiser le premier booléen
                    const size_t &moveType = item.first;
                    oss.write(reinterpret_cast<const char *>(&moveType), sizeof(size_t));

                    // Sérialiser les données du tuple
                    const auto &[x, y] = item.second;
                    oss.write(reinterpret_cast<const char *>(&x), sizeof(float));
                    oss.write(reinterpret_cast<const char *>(&y), sizeof(float));
                }
                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                if (component == nullptr) {
                    component = new EnemyMovementsComponent();
                }

                auto *enemyMovement = dynamic_cast<EnemyMovementsComponent *>(component);
                if (enemyMovement == nullptr) return nullptr;

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                // Désérialiser currentMove
                size_t move;
                iss.read(reinterpret_cast<char *>(&move), sizeof(size_t));
                enemyMovement->currentMove = move;

                // Désérialiser movementsQueueLoop
                enemyMovement->movementsQueueLoop.clear();
                while (iss.tellg() < static_cast<long long>(vec.size())) {
                    size_t moveType;
                    float  x, y;
                    iss.read(reinterpret_cast<char *>(&moveType), sizeof(size_t));
                    iss.read(reinterpret_cast<char *>(&x), sizeof(float));
                    iss.read(reinterpret_cast<char *>(&y), sizeof(float));
                    enemyMovement->movementsQueueLoop.emplace_back(moveType, sf::Vector2f(x, y));
                }

                return enemyMovement;
            }

            ComponentType getType() override
            {
                return ComponentType::EnemyMovementsComponent;
            }

            // these are the arguments to be passed to MovingComponent, they will be called each one after the other
            // in a loop.
            std::vector<std::pair<size_t, sf::Vector2f>> movementsQueueLoop;
            size_t                                       currentMove;

        private:
    };
} // namespace Engine::Components
