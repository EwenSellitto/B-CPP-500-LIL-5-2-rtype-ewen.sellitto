/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.hpp
*/

#pragma once

#include "ECS/System.hpp"
#include "ECS/Utilities.hpp"
#include "ECS/World.hpp"

enum class bulletType {
    Weak,
    Normal,
    Strong
};

namespace Engine::System
{
    class Bullets : public ECS::BaseSystem
    {
        public:
            Bullets(ECS::World &world) : ECS::BaseSystem(world) {}
            Bullets(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~Bullets() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time,
                             int dmg = 50);
            void spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time,
                             float rotation, int dmg = 50);
            void spawnBigBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time,
                                float rotation, int dmg = 50);

        private:
    };
} // namespace Engine::System
