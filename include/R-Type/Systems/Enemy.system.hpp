/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.hpp
*/

#pragma once

#include <chrono>
#include <utility>

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "SFML/System/Clock.hpp"
// #include "Components/Collision.component.hpp"

namespace EnemyData
{
    enum class EnemyType {
        Weak,
        Medium,
        Strong
    };

    struct EnemyAttributes {
            std::string spritePath;
            int         health;

            EnemyAttributes(std::string sprite, int hp) : spritePath(std::move(sprite)), health(hp) {}
    };

    const std::unordered_map<EnemyType, EnemyAttributes> enemyTypeAttributes = {
        {EnemyType::Weak, EnemyAttributes("./assets/klaed/Klaed-Scout-Base.png", 50)},
        {EnemyType::Medium, EnemyAttributes("./assets/klaed/Klaed-Battlecruiser-Base.png", 200)},
        {EnemyType::Strong, EnemyAttributes("./assets/klaed/Klaed-Dreadnought-Base.png", 2000)}};

    // {EnemyType::Weak, EnemyAttributes(spriteInfoMap.at("Klaed-Scout-Base").filePath , 50)},
    // {EnemyType::Medium, EnemyAttributes(spriteInfoMap.at("Klaed-Battlecruiser-Base").filePath, 100)},
    // {EnemyType::Strong, EnemyAttributes(spriteInfoMap.at("Klaed-Dreadnought-Base").filePath, 150)}};

} // namespace EnemyData
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
            void tryMakeEnemyAttack();

            // this spawnEnemy is deprecated, a factory inside EnemyQueue is used instead;
            size_t               spawnEnemy(float posx, float posy);
            bool                 shouldSpawnEnemy();
            EnemyData::EnemyType getRandomEnemyType();

        private:
            sf::Clock _clock;
    };
} // namespace Engine::System
