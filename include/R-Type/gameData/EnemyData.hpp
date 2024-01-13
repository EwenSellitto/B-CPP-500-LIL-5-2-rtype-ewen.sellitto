/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

#pragma once

#include <iostream>

namespace EnemyData
{
    enum class EnemyType {
        Weak,
        Medium,
        Strong
    };

    struct EnemyAttributes {
            std::string spritePath;
            int         health;

            EnemyAttributes(std::string sprite, int hp) : spritePath(std::move(sprite)), health(hp) {}
    };

    const std::unordered_map<EnemyType, EnemyAttributes> enemyTypeAttributes = {
        {EnemyType::Weak, EnemyAttributes("./assets/klaed/Klaed-Scout-Base.png", 50)},
        {EnemyType::Medium, EnemyAttributes("./assets/klaed/Klaed-Battlecruiser-Base.png", 100)},
        {EnemyType::Strong, EnemyAttributes("./assets/klaed/Klaed-Dreadnought-Base.png", 150)}};

} // namespace EnemyData
