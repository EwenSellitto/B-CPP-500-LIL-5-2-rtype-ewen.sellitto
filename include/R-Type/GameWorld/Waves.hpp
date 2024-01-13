/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Waves.hpp
*/

#pragma once

#ifndef WAVES_HPP_
#define WAVES_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "R-Type/Components/EnemyMovements.component.hpp"
#include "R-Type/Components/EnemyQueue.component.hpp"
#include "R-Type/GameWorld/Entities.hpp"

namespace Entities
{
    size_t basicEnemyMaker(float y, bool isAttacking, std::vector<std::pair<size_t, sf::Vector2f>> PatternMovements);
}

static const std::map<std::string, std::vector<std::pair<size_t, sf::Vector2f>>> enemyPatternMovements = {
    // Weak
    {"WeakUpAndDown", {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}},
    {"WeakLeft", {std::make_pair(800, sf::Vector2f(-100, 1))}},
    {"WeakDiagBotToTop", {std::make_pair(800, sf::Vector2f(-80, 60))}},
    {"WeakDiagTopToBot", {std::make_pair(800, sf::Vector2f(-80, -60))}},

    // Medium
    {"MediumUpAndDown", {std::make_pair(800, sf::Vector2f(-50, 50)), std::make_pair(800, sf::Vector2f(-50, -50))}},

    // Strong
    {"StrongUpAndDown", {std::make_pair(800, sf::Vector2f(-10, 70)), std::make_pair(800, sf::Vector2f(-10, -70))}},

};

#endif // WAVES_HPP_