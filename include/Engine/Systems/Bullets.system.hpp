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
#include "SFML/Window/Event.hpp"

enum class bulletType {
    Weak,
    Normal,
    Strong
};

// struct BulletsAttributes {
//         std::string spritePath;
//         int         _damage;
//         int         _speed;

//         BulletsAttributes(std::string sprite, int damage, int speed) : spritePath(sprite), _damage(damage),
//         _speed(speed) {}
// };

// const std::unordered_map<bulletType, BulletsAttributes> bulletTypeAttributes = {
//     {bulletType::Weak, BulletsAttributes("./assets/Nairan/Nairan-Scout-Base.png", 50, 10)},
//     {bulletType::Normal, BulletsAttributes("./assets/Nairan/Nairan-Battlecruiser-Base.png", 100, 15)},
//     {bulletType::Strong, BulletsAttributes("./assets/Nairan/Nairan-Dreadnought-Base.png", 150, 20)}};

namespace Engine::System
{
    class Bullets : public ECS::BaseSystem
    {
        public:
            Bullets(ECS::World &world) : ECS::BaseSystem(world), _clock()
            {

                _clock.restart();
            }
            Bullets(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids), _clock()
            {
                _clock.restart();
            }
            ~Bullets() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void spawnBullet(float posx, float posy, int direction);

        private:
            std::vector<ECS::Entity *> bullets = {};
            float                      speed   = 100;
            void                       addBullet(ECS::Entity *entity);
            sf::Clock                  _clock;
    };
} // namespace Engine::System
