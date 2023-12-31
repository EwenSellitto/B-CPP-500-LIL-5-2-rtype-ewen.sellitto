/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.hpp
*/

#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "SFML/System/Clock.hpp"

namespace EnemyData
{
    enum class EnemyType {
        Weak,
        Normal,
        Strong
    };

    struct EnemyAttributes {
            std::string spritePath;
            int         health;

            EnemyAttributes(std::string sprite, int hp) : spritePath(sprite), health(hp) {}
    };

    const std::unordered_map<EnemyType, EnemyAttributes> enemyTypeAttributes = {
        {EnemyType::Weak, EnemyAttributes("./assets/Nairan/Nairan-Scout-Base.png", 50)},
        {EnemyType::Normal, EnemyAttributes("./assets/Nairan/Nairan-Battlecruiser-Base.png", 100)},
        {EnemyType::Strong, EnemyAttributes("./assets/Nairan/Nairan-Dreadnought-Base.png", 150)}};

}
#ifndef ENEMY_SPAWN_RATE
#define ENEMY_SPAWN_RATE 500
#endif

namespace Engine::System
{
    class EnemySystem : public ECS::BaseSystem
    {
        public:
            EnemySystem(ECS::World &world) : ECS::BaseSystem(world), _clock()
            {
                _clock.restart();
//                spawnEnemy(300, 200);
            }
            EnemySystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids), _clock()
            {
                _clock.restart();
            }
            ~EnemySystem() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void tryChangeEnemiesMovement();
            void trySpawnEnemies();

            // this spawnEnemy is deprecated, a factory inside EnemyQueue is used instead;
            size_t      spawnEnemy(float posx, float posy);
            bool      shouldSpawnEnemy();
            EnemyData::EnemyType getRandomEnemyType();

        private:
            sf::Clock _clock;
    };
} // namespace Engine::System
