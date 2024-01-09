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
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components
{
    struct PlayerComponent : public ECS::BaseComponent {
        public:
            PlayerComponent() : playerNb(0){};

            PlayerComponent(int playerNb) : playerNb(playerNb){};

            ~PlayerComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);

                oss.write(reinterpret_cast<const char *>(&playerNb), sizeof(playerNb));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

            ECS::BaseComponent *deserialize(const std::vector<char> vec, ECS::BaseComponent *component) final
            {
                PlayerComponent *playerComponent;
                if (component == nullptr) {
                    playerComponent = new PlayerComponent();
                } else {
                    playerComponent = dynamic_cast<PlayerComponent *>(component);
                    if (playerComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);

                iss.read(reinterpret_cast<char *>(&playerComponent->playerNb), sizeof(playerComponent->playerNb));

                return playerComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::PlayerComponent;
            }

            int playerNb;
    };
} // namespace Engine::Components
