/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.hpp
*/

#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"

enum class EnemyType {
    Weak,
    Normal,
    Strong
};

struct EnemyAttributes {
    std::string spritePath;
    int health;

    EnemyAttributes(std::string sprite, int hp) : spritePath(sprite), health(hp) {}
};

const std::unordered_map<EnemyType, EnemyAttributes> enemyTypeAttributes = {
    {EnemyType::Weak, EnemyAttributes("./assets/Nairan/Nairan-Scout-Base.png", 50)},
    {EnemyType::Normal, EnemyAttributes("./assets/Nairan/Nairan-Battlecruiser-Base.png", 100)},
    {EnemyType::Strong, EnemyAttributes("./assets/Nairan/Nairan-Dreadnought-Base.png", 150)}
};

namespace Engine::System
{
    class EnemySystem : public ECS::BaseSystem
    {
        public:
            EnemySystem(ECS::World &world) : ECS::BaseSystem(world) {}
            EnemySystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~EnemySystem() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

        private:
            bool shouldSpawnEnemy();
            void spawnEnemy();
            EnemyType getRandomEnemyType();
    };
} // namespace Engine::System
