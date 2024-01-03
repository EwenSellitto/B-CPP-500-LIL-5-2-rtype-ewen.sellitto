/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"

namespace Engine::Components
{
    struct AnimationComponent : ECS::BaseComponent {
        public:
            AnimationComponent() = default;
            AnimationComponent(int x, int y, int width, int height, int tx, int ty, int animationSpeed, int frameCount)
                : textureRect(x, y, width, height), tileSize(tx, ty), animationSpeed(animationSpeed),
                  frameCount(frameCount){};
            ~AnimationComponent() = default;

            std::vector<char> serialize(void) override {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char*>(&textureRect.left), sizeof(textureRect.left));
                oss.write(reinterpret_cast<const char*>(&textureRect.top), sizeof(textureRect.top));
                oss.write(reinterpret_cast<const char*>(&textureRect.width), sizeof(textureRect.width));
                oss.write(reinterpret_cast<const char*>(&textureRect.height), sizeof(textureRect.height));
                oss.write(reinterpret_cast<const char*>(&tileSize.x), sizeof(tileSize.x));
                oss.write(reinterpret_cast<const char*>(&tileSize.y), sizeof(tileSize.y));
                oss.write(reinterpret_cast<const char*>(&frame), sizeof(frame));
                oss.write(reinterpret_cast<const char*>(&animationSpeed), sizeof(animationSpeed));
                oss.write(reinterpret_cast<const char*>(&frameCount), sizeof(frameCount));

                const std::string& str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr) {
                AnimationComponent* animationComponent;
                if (component == nullptr) {
                    animationComponent = new AnimationComponent();
                } else {
                    animationComponent = dynamic_cast<AnimationComponent*>(component);
                    if (animationComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char*>(&animationComponent->textureRect.left), sizeof(animationComponent->textureRect.left));
                iss.read(reinterpret_cast<char*>(&animationComponent->textureRect.top), sizeof(animationComponent->textureRect.top));
                iss.read(reinterpret_cast<char*>(&animationComponent->textureRect.width), sizeof(animationComponent->textureRect.width));
                iss.read(reinterpret_cast<char*>(&animationComponent->textureRect.height), sizeof(animationComponent->textureRect.height));
                iss.read(reinterpret_cast<char*>(&animationComponent->tileSize.x), sizeof(animationComponent->tileSize.x));
                iss.read(reinterpret_cast<char*>(&animationComponent->tileSize.y), sizeof(animationComponent->tileSize.y));
                iss.read(reinterpret_cast<char*>(&animationComponent->frame), sizeof(animationComponent->frame));
                iss.read(reinterpret_cast<char*>(&animationComponent->animationSpeed), sizeof(animationComponent->animationSpeed));
                iss.read(reinterpret_cast<char*>(&animationComponent->frameCount), sizeof(animationComponent->frameCount));

                return animationComponent;
            }

            // x, y = offset from topLeft; ex: 32x32 texture which contains a maximum size of 5x18 in the middle,
            //                   its x, y after looking are : 13, 10
            // width, height; ex: the 5, 18 in question.
            // tileSize (tx, ty);      ex: the 32, 32 in question.
            // animationSpeed in ms;
            sf::Rect<int> textureRect = {0, 0, 0, 0};
            sf::Vector2i  tileSize    = {0, 0};
            int           frame{0};
            int           animationSpeed{0};
            int           frameCount{0};
            sf::Clock     clock{};
    };
} // namespace Engine::Components
