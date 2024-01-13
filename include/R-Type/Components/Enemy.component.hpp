/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "ECS/Components.hpp"
#include "R-Type/gameData/EnemyData.hpp"

namespace Engine::Components
{
    struct EnemyComponent : ECS::BaseComponent {
        public:
            EnemyComponent() : enemyType(EnemyData::EnemyType::Weak) {}
            EnemyComponent(EnemyData::EnemyType enemyType) : enemyType(enemyType) {}
            ~EnemyComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                auto enemyTypeInt = static_cast<std::underlying_type<EnemyData::EnemyType>::type>(enemyType);
                oss.write(reinterpret_cast<const char *>(&enemyTypeInt), sizeof(enemyTypeInt));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                EnemyComponent *enemyComponent;
                if (component == nullptr) {
                    enemyComponent = new EnemyComponent(EnemyData::EnemyType::Weak); // Choix par défaut
                } else {
                    enemyComponent = dynamic_cast<EnemyComponent *>(component);
                    if (enemyComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                std::underlying_type<EnemyData::EnemyType>::type enemyTypeInt;
                iss.read(reinterpret_cast<char *>(&enemyTypeInt), sizeof(enemyTypeInt));
                enemyComponent->enemyType = static_cast<EnemyData::EnemyType>(enemyTypeInt);

                return enemyComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::EnemyComponent;
            }

            EnemyData::EnemyType enemyType;
    };
} // namespace Engine::Components
