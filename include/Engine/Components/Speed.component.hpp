/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <tuple>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace Engine::Components
{
    struct SpeedComponent : public ECS::BaseComponent {
        public:
            SpeedComponent(float speed) : speed(speed) {}

            ~SpeedComponent() override = default;

            std::vector<char> serialize(void) override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&speed), sizeof(speed));

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr)
            {
                SpeedComponent *speedComponent;
                if (component == nullptr) {
                    speedComponent = new SpeedComponent(0.0f);
                } else {
                    speedComponent = dynamic_cast<SpeedComponent *>(component);
                    if (speedComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&speedComponent->speed), sizeof(speedComponent->speed));

                return speedComponent;
            }

            float speed;

        private:
    };
} // namespace Engine::Components
