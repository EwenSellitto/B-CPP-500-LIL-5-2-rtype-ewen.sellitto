/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"

namespace Engine::Components
{
    struct BaseBulletComponent : public ECS::BaseComponent {
        public:
            explicit BaseBulletComponent(bool fromEnemy, int dmg = 2000, bool deleted = true)
                : fromEnemy(fromEnemy), damage(dmg), toDelete(deleted)
            {
            }
            ~BaseBulletComponent() override = default;

            bool fromEnemy;
            int  damage;
            bool toDelete;

        private:
    };
} // namespace Engine::Components
