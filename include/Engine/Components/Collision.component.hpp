/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "public/ComponentsType.hpp"

namespace Engine::Components
{
    struct CollisionComponent : public ECS::BaseComponent {
        public:
            explicit CollisionComponent(float off_x = 0, float off_y = 0, float size_x = 0, float size_y = 0)
                : rect(off_x, off_y, size_x, size_y)
            {
            }

            ~CollisionComponent() override = default;

            std::vector<char> serialize() override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&rect.left), sizeof(rect.left));
                oss.write(reinterpret_cast<const char *>(&rect.top), sizeof(rect.top));
                oss.write(reinterpret_cast<const char *>(&rect.width), sizeof(rect.width));
                oss.write(reinterpret_cast<const char *>(&rect.height), sizeof(rect.height));

                const std::string &str = oss.str();
                return {str.begin(), str.end()};
            }

             ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component) final
            {
                CollisionComponent *collisionComponent;
                if (component == nullptr) {
                    collisionComponent = new CollisionComponent();
                } else {
                    collisionComponent = dynamic_cast<CollisionComponent *>(component);
                    if (collisionComponent == nullptr) return nullptr;
                }

                std::istringstream iss(std::string(vec.begin(), vec.end()), std::ios::binary);
                iss.read(reinterpret_cast<char *>(&collisionComponent->rect.left),
                         sizeof(collisionComponent->rect.left));
                iss.read(reinterpret_cast<char *>(&collisionComponent->rect.top), sizeof(collisionComponent->rect.top));
                iss.read(reinterpret_cast<char *>(&collisionComponent->rect.width),
                         sizeof(collisionComponent->rect.width));
                iss.read(reinterpret_cast<char *>(&collisionComponent->rect.height),
                         sizeof(collisionComponent->rect.height));

                return collisionComponent;
            }

            ComponentType getType() override
            {
                return ComponentType::CollisionComponent;
            }

            sf::FloatRect rect;
    };
} // namespace Engine::Components

struct SpriteInfo {
        std::string filePath;
        int         offsetX;
        int         offsetY;
        int         width;
        int         height;
        int         oneframeX;
        int         oneframeY;
        int         nbFrames;
};

static const std::map<std::string, SpriteInfo> spriteInfoMap = {
    {"Asteroid-Flame", {"./assets/Environnement/Asteroid-Flame.png", 36, 32, 28508, 32, 96, 96, 3}},
    {"Asteroid01-Base", {"./assets/Environnement/Asteroid01-Base.png", 29, 32, 38, 33, 96, 96, 1}},
    {"Klaed-Battlecruiser-Base", {"./assets/klaed/Klaed-Battlecruiser-Base.png", 28, 12, 72, 89, 128, 128, 1}},
    {"Klaed-Battlecruiser-Destruction",
     {"./assets/klaed/Klaed-Battlecruiser-Destruction.png", 0, 0, 1792, 128, 128, 128, 14}},
    {"Klaed-Bullet", {"./assets/klaed/Klaed-Bullet.png", 1, 4, 2, 12, 4, 16, 4}},
    {"Klaed-Bomber-Base", {"./assets/klaed/Klaed-Bomber-Base.png", 17, 20, 30, 27, 64, 64, 1}},
    {"Klaed-Bomber-Destruction", {"./assets/klaed/Klaed-Bomber-Destruction.png", 0, 0, 512, 64, 64, 64, 8}},
    {"Klaed-Dreadnought-Base", {"./assets/klaed/Klaed-Dreadnought-Base.png", 28, 13, 72, 100, 128, 128, 1}},
    {"Klaed-Dreadnought-Destruction",
     {"./assets/klaed/Klaed-Dreadnought-Destruction.png", 0, 0, 1536, 128, 128, 128, 12}},
    {"Klaed-Fighter-Base", {"./assets/klaed/Klaed-Fighter-Base.png", 20, 21, 24, 22, 64, 64, 1}},
    {"Klaed-Fighter-Destruction", {"./assets/klaed/Klaed-Fighter-Destruction.png", 0, 0, 576, 64, 64, 64, 9}},
    {"Klaed-Frigate-Base", {"./assets/klaed/Klaed-Frigate-Base.png", 14, 11, 36, 39, 64, 64, 1}},
    {"Klaed-Frigate-Destruction", {"./assets/klaed/Klaed-Frigate-Destruction.png", 0, 0, 576, 64, 64, 64, 9}},
    {"Klaed-Scout-Base", {"./assets/klaed/Klaed-Scout-Base.png", 21, 23, 22, 22, 64, 64, 1}},
    {"Klaed-Scout-Destruction", {"./assets/klaed/Klaed-Scout-Destruction.png", 0, 0, 640, 64, 64, 64, 10}},
    {"Klaed-Supportship-Base", {"./assets/klaed/Klaed-Supportship-Base.png", 18, 15, 28, 28, 64, 64, 1}},
    {"Klaed-Supportship-Destruction", {"./assets/klaed/Klaed-Supportship-Destruction.png", 0, 0, 640, 64, 64, 64, 10}},
    {"Klaed-TorpedoShip-Base", {"./assets/klaed/Klaed-TorpedoShip-Base.png", 4, 21, 56, 22, 64, 64, 1}},
    {"Klaed-TorpedoShip-Destruction", {"./assets/klaed/Klaed-TorpedoShip-Destruction.png", 0, 0, 640, 64, 64, 64, 10}},
    {"MainShip-Base-Fullhealth", {"./assets/MainShip/MainShip-Base-Fullhealth.png", 9, 11, 30, 26, 48, 48, 1}},
    {"MainShip-Base-Destruction", {"./assets/MainShip/MainShip-Base-Destruction.png", 0, 0, 672, 48, 48, 48, 14}},
    {"MainshipWeapon-Projectile-Autocannonbullet",
     {"./assets/MainShipWeapons/MainshipWeapon-Projectile-Autocannonbullet.png", 11, 8, 10, 17, 32, 32, 4}}};
