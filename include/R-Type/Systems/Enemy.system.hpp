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
#include "R-Type/gameData/EnemyData.hpp"
#include "SFML/System/Clock.hpp"
// #include "Components/Collision.component.hpp"

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
            void tryMoveEnemies();
            void tryMakeEnemyAttack();

            // this spawnEnemy is deprecated, a factory inside EnemyQueue is used instead;
            size_t               spawnEnemy(float posx, float posy);
            bool                 shouldSpawnEnemy();
            EnemyData::EnemyType getRandomEnemyType();

        private:
            sf::Clock _clock;
    };
} // namespace Engine::System
