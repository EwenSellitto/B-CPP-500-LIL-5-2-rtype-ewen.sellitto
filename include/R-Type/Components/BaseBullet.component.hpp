/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct BaseBulletComponent : public ECS::BaseComponent {
        public:
            explicit BaseBulletComponent(bool fromEnemy) : fromEnemy(fromEnemy) {}
            ~BaseBulletComponent() override = default;

            std::vector<char> serialize(void) override {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char*>(&fromEnemy), sizeof(fromEnemy));

                const std::string& str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr) {
                BaseBulletComponent* bulletComponent;
                if (component == nullptr) {
                    bulletComponent = new BaseBulletComponent(false);
                } else {
                    bulletComponent = dynamic_cast<BaseBulletComponent*>(component);
                    if (bulletComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char*>(&bulletComponent->fromEnemy), sizeof(bulletComponent->fromEnemy));

                return bulletComponent;
            }

            bool fromEnemy;

        private:
    };
} // namespace Engine::Components
