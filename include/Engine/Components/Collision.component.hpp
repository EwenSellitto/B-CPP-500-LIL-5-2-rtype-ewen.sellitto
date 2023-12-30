/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderable.component.hpp
*/

#pragma once

#include <map>
#include <string>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include "ECS/Components.hpp"
#include "SFML/Graphics/Rect.hpp"

namespace Engine::Components
{
    struct CollisionComponent : public ECS::BaseComponent {
        public:
            explicit CollisionComponent(float off_x = 0, float off_y = 0, float size_x = 0, float size_y = 0)
                : rect(off_x, off_y, size_x, size_y)
            {
            }

            ~CollisionComponent() override = default;

            sf::FloatRect rect;
    };
} // namespace Engine::Components

struct SpriteInfo {
    std::string filePath;
    int width;
    int height;
    int oneframeX;
    int oneframeY;
    int nbFrames;
    int offsetX;
    int offsetY;
};

class SpriteData
{
    public:
        static std::map<std::string, SpriteInfo> spriteInfoMap;

        static void loadSprites()
        {
            // Environnement
            spriteInfoMap["Asteroid-Flame"] = {"../../assets/Environnement/assets/Environnement/Asteroid-Flame.png", 288, 96, 96, 96, 3, 36, 30};
            spriteInfoMap["Asteroid01-Base"] = {"../../assets/Environnement/assets/Environnement/Asteroid01-Base.png", 96, 96, 96, 96, 1, 28, 31};

            // klaed
            spriteInfoMap["Klaed-Battlecruiser-Base"] = {"../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Base.png", 128, 128, 128, 128, 1, 27, 12};
            spriteInfoMap["Klaed-Battlecruiser-Destruction"] = {"../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Destruction.png", 1792, 128, 128, 128, 14, 29, 14};
            spriteInfoMap["Klaed-Bullet"] = {"../../assets/klaed/assets/klaed/Klaed-Bullet.png", 16, 16, 4, 16, 4, 1, 4};

            // mainShip
            spriteInfoMap["MainShip-Base-Fullhealth"] = {"../../assets/MainShip/assets/MainShip/MainShip-Base-Fullhealth.png", 48, 48, 48, 48, 1, 9, 11};
            spriteInfoMap["MainShip-Base-Destruction"] = {"../../assets/MainShip/assets/MainShip/MainShip-Base-Destruction.png", 672, 48, 48, 48, 14, 9, 11};

            // MainShipWeapons
            spriteInfoMap["MainshipWeapon-Projectile-Autocannonbullet"] = {"../../assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-Autocannonbullet.png", 128, 32, 32, 32, 4, 15, 12};
        }
};
