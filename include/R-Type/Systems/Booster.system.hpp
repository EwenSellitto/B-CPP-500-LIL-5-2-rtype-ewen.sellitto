/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Booster.system.hpp
*/

#pragma once

#include "ECS/Entity.hpp"
#include "ECS/System.hpp"

namespace Rtype::System
{
    class BoosterSystem : public ECS::BaseSystem
    {
        public:
            BoosterSystem(ECS::World &world) : ECS::BaseSystem(world) {}
            BoosterSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~BoosterSystem() override = default;

            /**
             * @brief configure the system
             * @param world the world to configure
             */
            void configure([[maybe_unused]] ECS::World &world) override {}

            /**
             * @brief unconfigure the system
             * @param world the world to unconfigure
             */
            void unconfigure() override {}

            /**
             * @brief tick function called each frame
             */
            void tick() override;

            /**
             * @brief take the booster
             * @param player the player
             * @param booster the booster
             */
            static void takeBooster(ECS::Entity *player, ECS::Entity *booster);
    };
} // namespace Rtype::System
