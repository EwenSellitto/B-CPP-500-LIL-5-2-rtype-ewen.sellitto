/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Clock.hpp
*/

#pragma once

#ifndef SPRITE_DATA_HPP
#define SPRITE_DATA_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class SpriteData
{
    public:
        static std::map<std::string, sf::Sprite> sprites; // Map to store sprites

        static void loadSprites()
        {
            // Environnement
            sprites["Asteroid-Flame"] =
                createSprite("../../assets/Environnement/assets/Environnement/Asteroid-Flame.png", 480, 32, 32, 32);
            sprites["Asteroid01-Base"] =
                createSprite("../../assets/Environnement/assets/Environnement/Asteroid01-Base.png", 96, 96, 96, 96);
            sprites["Asteroid01-Explode"] =
                createSprite("../../assets/Environnement/assets/Environnement/Asteroid01-Explode.png", 768, 96, 96, 96);
            sprites["Earth-Likeplanet-Withoutbackglow"] =
                createSprite("../../assets/Environnement/assets/Environnement/Earth-Likeplanet-Withoutbackglow.png",
                             7392, 96, 96, 96);
            sprites["Earth-Likeplanet"] =
                createSprite("../../assets/Environnement/assets/Environnement/Earth-Likeplanet.png", 7392, 96, 96, 96);
            sprites["Starrybackground-Layer01-Solidcolour"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer01-Solidcolour.png",
                             5760, 360, 360, 360);
            sprites["Starrybackground-Layer01-Void"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer01-Void.png", 5760,
                             360, 360, 360);
            sprites["Starrybackground-Layer02-Shadows"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer02-Shadows.png",
                             5760, 360, 360, 360);
            sprites["Starrybackground-Layer02-Shadows2"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer02-Shadows2.png",
                             5760, 360, 360, 360);
            sprites["Starrybackground-Layer02-Stars"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer02-Stars.png", 5760,
                             360, 360, 360);
            sprites["Starrybackground-Layer03-Stars"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer03-Stars.png", 5760,
                             360, 360, 360);
            sprites["Starrybackground-Layer03-Stars2"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer03-Stars2.png",
                             5760, 360, 360, 360);
            sprites["Starrybackground-LayerX-BigStar"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-BigStar.png",
                             5760, 360, 360, 360);
            sprites["Starrybackground-LayerX-BigStar2"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-BigStar2.png",
                             5760, 360, 360, 360);
            sprites["Starrybackground-LayerX-Blackhole"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-Blackhole.png",
                             5760, 360, 360, 360);
            sprites["Starrybackground-LayerX-RotaryStar"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-RotaryStar.png",
                             5760, 360, 360, 360);
            sprites["Starrybackground-LayerX-RotaryStar2"] =
                createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-RotaryStar2.png",
                             5760, 360, 360, 360);

            // klaed
            sprites["Klaed-Battlecruiser-Base"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Base.png", 128, 128, 128, 128);
            sprites["Klaed-Battlecruiser-Destruction"] = createSprite(
                "../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Destruction.png", 1792, 128, 128, 128);
            sprites["Klaed-Battlecruiser-Engine"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Engine.png", 1536, 128, 128, 128);
            sprites["Klaed-Battlecruiser-Shield"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Shield.png", 2048, 128, 128, 128);
            sprites["Klaed-Battlecruiser-Weapons"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Weapons.png", 3840, 128, 128, 128);
            sprites["Klaed-BigBullet"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-BigBullet.png", 32, 16, 8, 16);
            sprites["Klaed-Bomber-Base"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Bomber-Base.png", 64, 64, 64, 64);
            sprites["Klaed-Bomber-Destruction"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Bomber-Destruction.png", 512, 64, 64, 64);
            sprites["Klaed-Bomber-Engine"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Bomber-Engine.png", 640, 64, 64, 64);
            sprites["Klaed-Bomber-Shield"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Bomber-Shield.png", 384, 64, 64, 64);
            sprites["Klaed-Dreadnought-Base"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Base.png", 128, 128, 128, 128);
            sprites["Klaed-Dreadnought-Destruction"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Destruction.png", 1536, 128, 128, 128);
            sprites["Klaed-Dreadnought-Engine"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Engine.png", 1536, 128, 128, 128);
            sprites["Klaed-Dreadnought-Shield"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Shield.png", 1280, 128, 128, 128);
            sprites["Klaed-Dreadnought-Weapons"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Weapons.png", 7680, 128, 128, 128);
            sprites["Klaed-Fighter-Base"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Base.png", 64, 64, 64, 64);
            sprites["Klaed-Fighter-Destruction"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Destruction.png", 576, 64, 64, 64);
            sprites["Klaed-Fighter-Engine"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Engine.png", 640, 64, 64, 64);
            sprites["Klaed-Fighter-Shield"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Shield.png", 512, 64, 64, 64);
            sprites["Klaed-Fighter-Weapons"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Weapons.png", 384, 64, 64, 64);
            sprites["Klaed-Frigate-Base"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Base.png", 64, 64, 64, 64);
            sprites["Klaed-Frigate-Destruction"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Destruction.png", 576, 64, 64, 64);
            sprites["Klaed-Frigate-Engine"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Engine.png", 768, 64, 64, 64);
            sprites["Klaed-Frigate-Shield"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Shield.png", 2560, 64, 64, 64);
            sprites["Klaed-Frigate-Weapons"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Weapons.png", 384, 64, 64, 64);
            sprites["Klaed-Ray"] = createSprite("../../assets/klaed/assets/klaed/Klaed-Ray.png", 72, 38, 18, 38);
            sprites["Klaed-Scout-Base"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Base.png", 64, 64, 64, 64);
            sprites["Klaed-Scout-Destruction"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Destruction.png", 640, 64, 64, 64);
            sprites["Klaed-Scout-Engine"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Engine.png", 640, 64, 64, 64);
            sprites["Klaed-Scout-Shield"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Shield.png", 896, 64, 64, 64);
            sprites["Klaed-Scout-Weapons"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Weapons.png", 384, 64, 64, 64);
            sprites["Klaed-Supportship-Base"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Supportship-Base.png", 64, 64, 64, 64);
            sprites["Klaed-Supportship-Destruction"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Supportship-Destruction.png", 640, 64, 64, 64);
            sprites["Klaed-Supportship-Engine"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Supportship-Engine.png", 640, 64, 64, 64);
            sprites["Klaed-Torpedo"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-Torpedo.png", 33, 32, 11, 32);
            sprites["Klaed-TorpedoShip-Base"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Base.png", 64, 64, 64, 64);
            sprites["Klaed-TorpedoShip-Destruction"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Destruction.png", 640, 64, 64, 64);
            sprites["Klaed-TorpedoShip-Engine"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Engine.png", 640, 64, 64, 64);
            sprites["Klaed-TorpedoShip-Shield"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Shield.png", 640, 64, 64, 64);
            sprites["Klaed-TorpedoShip-Weapons"] =
                createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Weapons.png", 1024, 64, 64, 64);
            sprites["Klaed-Wave"] = createSprite("../../assets/klaed/assets/klaed/Klaed-Wave.png", 384, 64, 64, 64);

            // MainShip
            sprites["MainShip-Base-Damaged"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Base-Damaged.png", 48, 48, 48, 48);
            sprites["MainShip-Base-Fullhealth"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Base-Fullhealth.png", 48, 48, 48, 48);
            sprites["MainShip-Base-Slightdamage"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Base-Slightdamage.png", 48, 48, 48, 48);
            sprites["MainShip-Base-Verydamaged"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Base-Verydamaged.png", 48, 48, 48, 48);
            sprites["MainShip-Engines-BaseEngine-Idle"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine-Idle.png", 144, 48, 48, 48);
            sprites["MainShip-Engines-BaseEngine-Powering"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine-Powering.png", 192, 48, 48, 48);
            sprites["MainShip-Engines-BaseEngine"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine.png", 48, 48, 48, 48);
            sprites["MainShip-Engines-BigPulseEngine-Idle"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine-Idle.png", 192, 48, 48, 48);
            sprites["MainShip-Engines-BigPulseEngine-Powering"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine-Powering.png", 192, 48, 48, 48);
            sprites["MainShip-Engines-BigPulseEngine"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine.png", 48, 48, 48, 48);
            sprites["MainShip-Engines-BurstEngine-Idle"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine-Idle.png", 336, 48, 48, 48);
            sprites["MainShip-Engines-BurstEngine-Powering"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine-Powering.png", 288, 48, 48, 48);
            sprites["MainShip-Engines-BurstEngine"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine.png", 48, 48, 48, 48);
            sprites["MainShip-Engines-SuperchargedEngine-Idle"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine-Idle.png", 192, 48, 48, 48);
            sprites["MainShip-Engines-SuperchargedEngine-Powering"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine-Powering.png",
                             192, 48, 48, 48);
            sprites["MainShip-Engines-SuperchargedEngine"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine.png", 48, 48, 48, 48);
            sprites["MainShip-Shields-FrontandSideShield"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Shields-FrontandSideShield.png", 384, 64, 64, 64);
            sprites["MainShip-Shields-FrontShield"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Shields-FrontShield.png", 640, 64, 64, 64);
            sprites["MainShip-Shields-InvincibilityShield"] = createSprite(
                "../../assets/MainShip/assets/MainShip/MainShip-Shields-InvincibilityShield.png", 640, 64, 64, 64);
            sprites["MainShip-Shields-RoundShield"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Shields-RoundShield.png", 768, 64, 64, 64);
            sprites["MainShip-Weapons-AutoCannon"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Weapons-AutoCannon.png", 336, 48, 48, 48);
            sprites["MainShip-Weapons-BigSpaceGun"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Weapons-BigSpaceGun.png", 576, 48, 48, 48);
            sprites["MainShip-Weapons-Rockets"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Weapons-Rockets.png", 816, 48, 48, 48);
            sprites["MainShip-Weapons-Zapper"] =
                createSprite("../../assets/MainShip/assets/MainShip/MainShip-Weapons-Zapper.png", 672, 48, 48, 48);
            // Add more sprites as needed...
        }

    private:
        static sf::Sprite createSprite(const std::string &file, int width, int height, int offsetX, int offsetY)
        {
            sf::Sprite  sprite;
            sf::Texture texture;
            if (!texture.loadFromFile(file)) {
                // Handle failed texture load
                return sprite; // Return empty sprite
            }
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(0, 0, width, height));
            sprite.setPosition(offsetX, offsetY);
            return sprite;
        }
};

std::map<std::string, sf::Sprite> SpriteData::sprites; // Definition of static member

#endif // SPRITE_DATA_HPP
