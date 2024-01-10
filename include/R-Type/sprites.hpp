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

// sprites["Asteroid-Flame"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Asteroid-Flame.png", 480, 32, 32, 32);
// sprites["Asteroid01-Base"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Asteroid01-Base.png", 96, 96, 96, 96);
// sprites["Asteroid01-Explode"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Asteroid01-Explode.png", 768, 96, 96, 96);
// sprites["Earth-Likeplanet-Withoutbackglow"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Earth-Likeplanet-Withoutbackglow.png",
//                     7392, 96, 96, 96);
// sprites["Earth-Likeplanet"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Earth-Likeplanet.png", 7392, 96, 96, 96);
// sprites["Starrybackground-Layer01-Solidcolour"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer01-Solidcolour.png",
//                     5760, 360, 360, 360);
// sprites["Starrybackground-Layer01-Void"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer01-Void.png", 5760,
//                     360, 360, 360);
// sprites["Starrybackground-Layer02-Shadows"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer02-Shadows.png",
//                     5760, 360, 360, 360);
// sprites["Starrybackground-Layer02-Shadows2"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer02-Shadows2.png",
//                     5760, 360, 360, 360);
// sprites["Starrybackground-Layer02-Stars"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer02-Stars.png", 5760,
//                     360, 360, 360);
// sprites["Starrybackground-Layer03-Stars"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer03-Stars.png", 5760,
//                     360, 360, 360);
// sprites["Starrybackground-Layer03-Stars2"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-Layer03-Stars2.png",
//                     5760, 360, 360, 360);
// sprites["Starrybackground-LayerX-BigStar"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-BigStar.png",
//                     5760, 360, 360, 360);
// sprites["Starrybackground-LayerX-BigStar2"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-BigStar2.png",
//                     5760, 360, 360, 360);
// sprites["Starrybackground-LayerX-Blackhole"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-Blackhole.png",
//                     5760, 360, 360, 360);
// sprites["Starrybackground-LayerX-RotaryStar"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-RotaryStar.png",
//                     5760, 360, 360, 360);
// sprites["Starrybackground-LayerX-RotaryStar2"] =
//     createSprite("../../assets/Environnement/assets/Environnement/Starrybackground-LayerX-RotaryStar2.png",
//                     5760, 360, 360, 360);

// // klaed
// sprites["Klaed-Battlecruiser-Base"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Base.png", 128, 128, 128, 128);
// sprites["Klaed-Battlecruiser-Destruction"] = createSprite(
//     "../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Destruction.png", 1792, 128, 128, 128);
// sprites["Klaed-Battlecruiser-Engine"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Engine.png", 1536, 128, 128, 128);
// sprites["Klaed-Battlecruiser-Shield"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Shield.png", 2048, 128, 128, 128);
// sprites["Klaed-Battlecruiser-Weapons"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Battlecruiser-Weapons.png", 3840, 128, 128, 128);
// sprites["Klaed-BigBullet"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-BigBullet.png", 32, 16, 8, 16);
// sprites["Klaed-Bomber-Base"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Bomber-Base.png", 64, 64, 64, 64);
// sprites["Klaed-Bomber-Destruction"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Bomber-Destruction.png", 512, 64, 64, 64);
// sprites["Klaed-Bomber-Engine"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Bomber-Engine.png", 640, 64, 64, 64);
// sprites["Klaed-Bomber-Shield"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Bomber-Shield.png", 384, 64, 64, 64);
// sprites["Klaed-Dreadnought-Base"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Base.png", 128, 128, 128, 128);
// sprites["Klaed-Dreadnought-Destruction"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Destruction.png", 1536, 128, 128, 128);
// sprites["Klaed-Dreadnought-Engine"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Engine.png", 1536, 128, 128, 128);
// sprites["Klaed-Dreadnought-Shield"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Shield.png", 1280, 128, 128, 128);
// sprites["Klaed-Dreadnought-Weapons"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Dreadnought-Weapons.png", 7680, 128, 128, 128);
// sprites["Klaed-Fighter-Base"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Base.png", 64, 64, 64, 64);
// sprites["Klaed-Fighter-Destruction"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Destruction.png", 576, 64, 64, 64);
// sprites["Klaed-Fighter-Engine"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Engine.png", 640, 64, 64, 64);
// sprites["Klaed-Fighter-Shield"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Shield.png", 512, 64, 64, 64);
// sprites["Klaed-Fighter-Weapons"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Fighter-Weapons.png", 384, 64, 64, 64);
// sprites["Klaed-Frigate-Base"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Base.png", 64, 64, 64, 64);
// sprites["Klaed-Frigate-Destruction"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Destruction.png", 576, 64, 64, 64);
// sprites["Klaed-Frigate-Engine"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Engine.png", 768, 64, 64, 64);
// sprites["Klaed-Frigate-Shield"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Shield.png", 2560, 64, 64, 64);
// sprites["Klaed-Frigate-Weapons"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Frigate-Weapons.png", 384, 64, 64, 64);
// sprites["Klaed-Ray"] = createSprite("../../assets/klaed/assets/klaed/Klaed-Ray.png", 72, 38, 18, 38);
// sprites["Klaed-Scout-Base"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Base.png", 64, 64, 64, 64);
// sprites["Klaed-Scout-Destruction"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Destruction.png", 640, 64, 64, 64);
// sprites["Klaed-Scout-Engine"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Engine.png", 640, 64, 64, 64);
// sprites["Klaed-Scout-Shield"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Shield.png", 896, 64, 64, 64);
// sprites["Klaed-Scout-Weapons"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Scout-Weapons.png", 384, 64, 64, 64);
// sprites["Klaed-Supportship-Base"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Supportship-Base.png", 64, 64, 64, 64);
// sprites["Klaed-Supportship-Destruction"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Supportship-Destruction.png", 640, 64, 64, 64);
// sprites["Klaed-Supportship-Engine"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Supportship-Engine.png", 640, 64, 64, 64);
// sprites["Klaed-Torpedo"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-Torpedo.png", 33, 32, 11, 32);
// sprites["Klaed-TorpedoShip-Base"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Base.png", 64, 64, 64, 64);
// sprites["Klaed-TorpedoShip-Destruction"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Destruction.png", 640, 64, 64, 64);
// sprites["Klaed-TorpedoShip-Engine"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Engine.png", 640, 64, 64, 64);
// sprites["Klaed-TorpedoShip-Shield"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Shield.png", 640, 64, 64, 64);
// sprites["Klaed-TorpedoShip-Weapons"] =
//     createSprite("../../assets/klaed/assets/klaed/Klaed-TorpedoShip-Weapons.png", 1024, 64, 64, 64);
// sprites["Klaed-Wave"] = createSprite("../../assets/klaed/assets/klaed/Klaed-Wave.png", 384, 64, 64, 64);

// // MainShip
// sprites["MainShip-Base-Damaged"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Base-Damaged.png", 48, 48, 48, 48);
// sprites["MainShip-Base-Fullhealth"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Base-Fullhealth.png", 48, 48, 48, 48);
// sprites["MainShip-Base-Slightdamage"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Base-Slightdamage.png", 48, 48, 48, 48);
// sprites["MainShip-Base-Verydamaged"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Base-Verydamaged.png", 48, 48, 48, 48);
// sprites["MainShip-Engines-BaseEngine-Idle"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine-Idle.png", 144, 48, 48, 48);
// sprites["MainShip-Engines-BaseEngine-Powering"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine-Powering.png", 192, 48, 48, 48);
// sprites["MainShip-Engines-BaseEngine"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Engines-BaseEngine.png", 48, 48, 48, 48);
// sprites["MainShip-Engines-BigPulseEngine-Idle"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine-Idle.png", 192, 48, 48, 48);
// sprites["MainShip-Engines-BigPulseEngine-Powering"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine-Powering.png", 192, 48, 48, 48);
// sprites["MainShip-Engines-BigPulseEngine"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-BigPulseEngine.png", 48, 48, 48, 48);
// sprites["MainShip-Engines-BurstEngine-Idle"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine-Idle.png", 336, 48, 48, 48);
// sprites["MainShip-Engines-BurstEngine-Powering"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine-Powering.png", 288, 48, 48, 48);
// sprites["MainShip-Engines-BurstEngine"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Engines-BurstEngine.png", 48, 48, 48, 48);
// sprites["MainShip-Engines-SuperchargedEngine-Idle"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine-Idle.png", 192, 48, 48, 48);
// sprites["MainShip-Engines-SuperchargedEngine-Powering"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine-Powering.png",
//                     192, 48, 48, 48);
// sprites["MainShip-Engines-SuperchargedEngine"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Engines-SuperchargedEngine.png", 48, 48, 48, 48);
// sprites["MainShip-Shields-FrontandSideShield"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Shields-FrontandSideShield.png", 384, 64, 64, 64);
// sprites["MainShip-Shields-FrontShield"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Shields-FrontShield.png", 640, 64, 64, 64);
// sprites["MainShip-Shields-InvincibilityShield"] = createSprite(
//     "../../assets/MainShip/assets/MainShip/MainShip-Shields-InvincibilityShield.png", 640, 64, 64, 64);
// sprites["MainShip-Shields-RoundShield"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Shields-RoundShield.png", 768, 64, 64, 64);
// sprites["MainShip-Weapons-AutoCannon"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Weapons-AutoCannon.png", 336, 48, 48, 48);
// sprites["MainShip-Weapons-BigSpaceGun"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Weapons-BigSpaceGun.png", 576, 48, 48, 48);
// sprites["MainShip-Weapons-Rockets"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Weapons-Rockets.png", 816, 48, 48, 48);
// sprites["MainShip-Weapons-Zapper"] =
//     createSprite("../../assets/MainShip/assets/MainShip/MainShip-Weapons-Zapper.png", 672, 48, 48, 48);

// // MainShipWeapons
// sprites["MainshipWeapon-Projectile-Autocannonbullet"] = createSprite(
//     "../../assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-Autocannonbullet.png",
//     128, 32, 32, 32);
// sprites["MainshipWeapon-Projectile-BigSpaceGun"] = createSprite(
//     "../../assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-BigSpaceGun.png", 320,
//     32, 32, 32);
// sprites["MainshipWeapon-Projectile-Rocket"] =
//     createSprite("../../assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-Rocket.png",
//                     96, 32, 32, 32);
// sprites["MainshipWeapon-Projectile-Zapper"] =
//     createSprite("../../assets/MainShipWeapons/assets/MainShipWeapons/MainshipWeapon-Projectile-Zapper.png",
//                     256, 32, 32, 32);

// // Nairan
// sprites["Nairan-Battlecruiser-Base"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Base.png", 128, 128, 128, 128);
// sprites["Nairan-Battlecruiser-Destruction"] = createSprite(
//     "../../assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Destruction.png", 2304, 128, 128, 128);
// sprites["Nairan-Battlecruiser-Engine"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Engine.png", 1024, 128, 128, 128);
// sprites["Nairan-Battlecruiser-Shield"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Shield.png", 1024, 128, 128, 128);
// sprites["Nairan-Battlecruiser-Weapons"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Battlecruiser-Weapons.png", 1152, 128, 128, 128);
// sprites["Nairan-Bolt"] = createSprite("../../assets/Nairan/assets/Nairan/Nairan-Bolt.png", 45, 9, 9, 9);
// sprites["Nairan-Bomber-Base"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Bomber-Base.png", 64, 64, 64, 64);
// sprites["Nairan-Bomber-Destruction"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Bomber-Destruction.png", 1024, 64, 64, 64);
// sprites["Nairan-Bomber-Engine"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Bomber-Engine.png", 512, 64, 64, 64);
// sprites["Nairan-Bomber-Shield"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Bomber-Shield.png", 640, 64, 64, 64);
// sprites["Nairan-Dreadnought-Base"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Dreadnought-Base.png", 128, 128, 128, 128);
// sprites["Nairan-Dreadnought-Destruction"] = createSprite(
//     "../../assets/Nairan/assets/Nairan/Nairan-Dreadnought-Destruction.png", 2304, 128, 128, 128);
// sprites["Nairan-Dreadnought-Engine"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Dreadnought-Engine.png", 1024, 128, 128, 128);
// sprites["Nairan-Dreadnought-Shield"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Dreadnought-Shield.png", 640, 128, 128, 128);
// sprites["Nairan-Dreadnought-Weapons"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Dreadnought-Weapons.png", 4352, 128, 128, 128);
// sprites["Nairan-Fighter-Base"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Fighter-Base.png", 64, 64, 64, 64);
// sprites["Nairan-Fighter-Destruction"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Fighter-Destruction.png", 1152, 64, 64, 64);
// sprites["Nairan-Fighter-Engine"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Fighter-Engine.png", 512, 64, 64, 64);
// sprites["Nairan-Fighter-Shield"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Fighter-Shield.png", 1280, 64, 64, 64);
// sprites["Nairan-Fighter-Weapons"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Fighter-Weapons.png", 1792, 64, 64, 64);
// sprites["Nairan-Frigate-Base"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Frigate-Base.png", 64, 64, 64, 64);
// sprites["Nairan-Frigate-Destruction"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Frigate-Destruction.png", 1024, 64, 64, 64);
// sprites["Nairan-Frigate-Engine"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Frigate-Engine.png", 512, 64, 64, 64);
// sprites["Nairan-Frigate-Shield"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Frigate-Shield.png", 512, 64, 64, 64);
// sprites["Nairan-Frigate-Weapons"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Frigate-Weapons.png", 320, 64, 64, 64);
// sprites["Nairan-Ray"] = createSprite("../../assets/Nairan/assets/Nairan/Nairan-Ray.png", 72, 38, 18, 38);
// sprites["Nairan-Rocket"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Rocket.png", 36, 16, 9, 16);
// sprites["Nairan-Scout-Base"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Scout-Base.png", 64, 64, 64, 64);
// sprites["Nairan-Scout-Destruction"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Scout-Destruction.png", 1024, 64, 64, 64);
// sprites["Nairan-Scout-Engine"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Scout-Engine.png", 512, 64, 64, 64);
// sprites["Nairan-Scout-Shield"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Scout-Shield.png", 1152, 64, 64, 64);
// sprites["Nairan-Scout-Weapons"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Scout-Weapons.png", 384, 64, 64, 64);
// sprites["Nairan-SupportShip-Base"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-SupportShip-Base.png", 64, 64, 64, 64);
// sprites["Nairan-SupportShip-Destruction"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-SupportShip-Destruction.png", 1024, 64, 64, 64);
// sprites["Nairan-SupportShip-Engine"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-SupportShip-Engine.png", 512, 64, 64, 64);
// sprites["Nairan-Torpedo"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-Torpedo.png", 27, 24, 9, 24);
// sprites["Nairan-TorpedoShip-Base"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Base.png", 64, 64, 64, 64);
// sprites["Nairan-TorpedoShip-Destruction"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Destruction.png", 1024, 64, 64, 64);
// sprites["Nairan-TorpedoShip-Engine"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Engine.png", 512, 64, 64, 64);
// sprites["Nairan-TorpedoShip-Shield"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Shield.png", 512, 64, 64, 64);
// sprites["Nairan-TorpedoShip-Weapons"] =
//     createSprite("../../assets/Nairan/assets/Nairan/Nairan-TorpedoShip-Weapons.png", 768, 64, 64, 64);

// // Pickup
// sprites["PickupIcon-Engines-BaseEngine"] =
//     createSprite("../../assets/Pickup/assets/Pickup/PickupIcon-Engines-BaseEngine.png", 480, 32, 32, 32);
// sprites["PickupIcon-Engines-BigPulseEngine"] = createSprite(
//     "../../assets/Pickup/assets/Pickup/PickupIcon-Engines-BigPulseEngine.png", 480, 32, 32, 32);
// sprites["PickupIcon-Engines-BurstEngine"] =
//     createSprite("../../assets/Pickup/assets/Pickup/PickupIcon-Engines-BurstEngine.png", 480, 32, 32, 32);
// sprites["PickupIcon-Engines-SuperchargedEngine"] = createSprite(
//     "../../assets/Pickup/assets/Pickup/PickupIcon-Engines-SuperchargedEngine.png", 480, 32, 32, 32);
// sprites["PickupIcon-ShieldGenerator-Allaroundshield"] = createSprite(
//     "../../assets/Pickup/assets/Pickup/PickupIcon-ShieldGenerator-Allaroundshield.png", 480, 32, 32, 32);
// sprites["PickupIcon-ShieldGenerator-FrontandSideShield"] = createSprite(
//     "../../assets/Pickup/assets/Pickup/PickupIcon-ShieldGenerator-FrontandSideShield.png", 480, 32, 32, 32);
// sprites["PickupIcon-ShieldGenerator-FrontShield"] = createSprite(
//     "../../assets/Pickup/assets/Pickup/PickupIcon-ShieldGenerator-FrontShield.png", 480, 32, 32, 32);
// sprites["PickupIcon-ShieldGenerator-InvincibilityShield"] =
//     createSprite("../../assets/Pickup/assets/Pickup/PickupIcon-ShieldGenerator-InvincibilityShield.png",
//                     480, 32, 32, 32);
// sprites["PickupIcon-Weapons-AutoCannons"] =
//     createSprite("../../assets/Pickup/assets/Pickup/PickupIcon-Weapons-AutoCannons.png", 480, 32, 32, 32);
// sprites["PickupIcon-Weapons-BigSpaceGun2000"] = createSprite(
//     "../../assets/Pickup/assets/Pickup/PickupIcon-Weapons-BigSpaceGun2000.png", 480, 32, 32, 32);
// sprites["PickupIcon-Weapons-Rockets"] =
//     createSprite("../../assets/Pickup/assets/Pickup/PickupIcon-Weapons-Rockets.png", 480, 32, 32, 32);
// sprites["PickupIcon-Weapons-Zapper"] =
//     createSprite("../../assets/Pickup/assets/Pickup/PickupIcon-Weapons-Zapper.png", 480, 32, 32, 32);

#endif // SPRITE_DATA_HPP
