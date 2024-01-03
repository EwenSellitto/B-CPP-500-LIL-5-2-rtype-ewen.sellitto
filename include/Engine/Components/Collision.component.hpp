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

            std::vector<char> serialize(void) override
            {
                std::ostringstream oss(std::ios::binary);
                oss.write(reinterpret_cast<const char *>(&rect.left), sizeof(rect.left));
                oss.write(reinterpret_cast<const char *>(&rect.top), sizeof(rect.top));
                oss.write(reinterpret_cast<const char *>(&rect.width), sizeof(rect.width));
                oss.write(reinterpret_cast<const char *>(&rect.height), sizeof(rect.height));

                const std::string &str = oss.str();
                return std::vector<char>(str.begin(), str.end());
            }

            static ECS::BaseComponent *deserialize(std::vector<char> vec, ECS::BaseComponent *component = nullptr)
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

            sf::FloatRect rect;
    };
} // namespace Engine::Components

struct SpriteInfo {
        std::string filePath;
        int         width;
        int         height;
        int         oneframeX;
        int         oneframeY;
        int         nbFrames;
        int         offsetX;
        int         offsetY;
};

class SpriteData
{
    public:
        static std::map<std::string, SpriteInfo> spriteInfoMap;

        static void loadSprites()
        {
            // Environnement
            spriteInfoMap["Asteroid-Flame"] = {
                "../../assets/Environnement/assets/Environnement/Asteroid-Flame.png", 288, 96, 96, 96, 3, 36, 30};
            spriteInfoMap["Asteroid01-Base"] = {
                "../../assets/Environnement/assets/Environnement/Asteroid01-Base.png", 96, 96, 96, 96, 1, 28, 31};

            // klaed
            spriteInfoMap["Klaed-Battlecruiser-Base"] = {
                "../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Base.png", 128, 128, 128, 128, 1, 27, 12};
            spriteInfoMap["Klaed-Battlecruiser-Destruction"] = {
                "../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Destruction.png", 1792, 128, 128, 128, 14, 27, 12};
            spriteInfoMap["Klaed-Bullet"] = {
                "../../assets/klaed/assets/klaed/Klaed-Bullet.png", 16, 16, 4, 16, 4, 1, 4};
            spriteInfoMap["Klaed-Bomber-Base"] = {
                "../../assets/klaed/assets/klaed/Klaed-Bomber-Base.png", 64, 64, 64, 64, 1, 17, 20};
            spriteInfoMap["Klaed-Bomber-Destruction"] = {
                "../../assets/klaed/assets/klaed/Klaed-Bomber-Destruction.png", 512, 64, 64, 64, 8, 0, 0};
            spriteInfoMap["Klaed-Dreadnought-Base"] = {
                "../../assets/klaed/assets/klaed/Klaed-Dreadnought-Base.png", 128, 128, 128, 128, 1, 28, 13};
            spriteInfoMap["Klaed-Dreadnought-Destruction"] = {
                "../../assets/klaed/assets/klaed/Klaed-Dreadnought-Destruction.png", 1536, 128, 128, 128, 12, 0, 0};
            spriteInfoMap["Klaed-Fighter-Base"] = {
                "../../assets/klaed/assets/klaed/Klaed-Fighter-Base.png", 64, 64, 64, 64, 1, 20, 21};
            spriteInfoMap["Klaed-Fighter-Destruction"] = {
                "../../assets/klaed/assets/klaed/Klaed-Fighter-Destruction.png", 576, 64, 64, 64, 9, 0, 0};
            spriteInfoMap["Klaed-Frigate-Base"] = {
                "../../assets/klaed/assets/klaed/Klaed-Frigate-Base.png", 64, 64, 64, 64, 1, 14, 11};
            spriteInfoMap["Klaed-Frigate-Destruction"] = {
                "../../assets/klaed/assets/klaed/Klaed-Frigate-Destruction.png", 576, 64, 64, 64, 9, 0, 0};
            spriteInfoMap["Klaed-Scout-Base"] = {
                "../../assets/klaed/assets/klaed/Klaed-Scout-Base.png", 64, 64, 64, 64, 1, 21, 23};
            spriteInfoMap["Klaed-Scout-Destruction"] = {
                "../../assets/klaed/assets/klaed/Klaed-Scout-Destruction.png", 640, 64, 64, 64, 10, 0, 0};
            spriteInfoMap["Klaed-Supportship-Base"] = {
                "../../assets/klaed/assets/klaed/Klaed-Supportship-Base.png", 64, 64, 64, 64, 1, 18, 15};
            spriteInfoMap["Klaed-Supportship-Destruction"] = {
                "../../assets/klaed/assets/klaed/Klaed-Supportship-Destruction.png", 640, 64, 64, 64, 10, 0, 7};
            spriteInfoMap["Klaed-TorpedoShip-Base"] = {
                "../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Base.png", 64, 64, 64, 64, 1, 4, 21};
            spriteInfoMap["Klaed-TorpedoShip-Destruction"] = {
                "../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Destruction.png", 640, 64, 64, 64, 10, 0, 0};

            // mainShip
            spriteInfoMap["MainShip-Base-Fullhealth"] = {
                "../../assets/MainShip/assets/MainShip/MainShip-Base-Fullhealth.png", 48, 48, 48, 48, 1, 9, 11};
            spriteInfoMap["MainShip-Base-Destruction"] = {
                "../../assets/MainShip/assets/MainShip/MainShip-Base-Destruction.png", 672, 48, 48, 48, 14, 9, 11};

            // MainShipWeapons
            spriteInfoMap["MainshipWeapon-Projectile-Autocannonbullet"] = {
                "../../assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-Autocannonbullet.png",
                128,
                32,
                32,
                32,
                4,
                15,
                12};
        }
};
