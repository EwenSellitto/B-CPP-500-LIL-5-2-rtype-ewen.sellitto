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

namespace Engine::Components
{
    struct BaseBulletComponent : public ECS::BaseComponent {
        public:
            BaseBulletComponent() : fromEnemy(false), damage(2000), toDelete(true) {}
            explicit BaseBulletComponent(bool fromEnemy, int dmg = 2000, bool deleted = true)
                : fromEnemy(fromEnemy), damage(dmg), toDelete(deleted)
            {
            }
            ~BaseBulletComponent() override = default;

            std::vector<char> serialize(void) override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&fromEnemy), sizeof(fromEnemy));
                oss.write(reinterpret_cast<const char *>(&damage), sizeof(damage));
                oss.write(reinterpret_cast<const char *>(&toDelete), sizeof(toDelete));

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                BaseBulletComponent *bulletComponent;
                if (component == nullptr) {
                    bulletComponent = new BaseBulletComponent(false);
                } else {
                    bulletComponent = dynamic_cast<BaseBulletComponent *>(component);
                    if (bulletComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&bulletComponent->fromEnemy), sizeof(bulletComponent->fromEnemy));
                iss.read(reinterpret_cast<char *>(&bulletComponent->damage), sizeof(bulletComponent->damage));
                iss.read(reinterpret_cast<char *>(&bulletComponent->toDelete), sizeof(bulletComponent->toDelete));

                return bulletComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::BaseBulletComponent;
            }

            bool fromEnemy;
            int  damage;
            bool toDelete;

        private:
    };
} // namespace Engine::Components
