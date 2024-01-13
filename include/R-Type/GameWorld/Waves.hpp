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

// Rest of the code

static const std::map<std::string, std::vector<std::pair<size_t, sf::Vector2f>>> enemyPatternMovements = {
    // Weak
    {"WeakUpAndDown", {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}},
    {"WeakLeft", {std::make_pair(800, sf::Vector2f(-100, 1))}},
    {"WeakDiagBotToTop", {std::make_pair(800, sf::Vector2f(-80, 60))}},
    {"WeakDiagTopToBot", {std::make_pair(800, sf::Vector2f(-80, -60))}},

    // Medium
    {"MediumUpAndDown", {std::make_pair(800, sf::Vector2f(-50, 50)), std::make_pair(800, sf::Vector2f(-50, -50))}},
};

// pos_x and pos_y are the position of the first enemy of the wave (top left corner or 1st enemy of the wave)

// std::vector<std::pair<bool, std::pair<std::tuple<size_t, float, bool>, std::function<size_t (float, bool)>>>>
// TwinSnake(int pos_x, int pos_y) {

//     return {
//     // twin snake 1
//     std::make_pair(false, std::make_pair(std::make_tuple(160, 200, false), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(170, 210, true), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(180, 220, false), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(190, 230, false), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(200, 240, true), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(210, 250, true), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(220, 260, false), Entities::basicEnemyMaker)),

//     // twin snake 2
//     std::make_pair(false, std::make_pair(std::make_tuple(160, 350, false), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(170, 360, true), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(180, 370, false), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(190, 380, true), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(200, 390, true), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(210, 400, false), Entities::basicEnemyMaker)),
//     std::make_pair(false, std::make_pair(std::make_tuple(220, 410, false), Entities::basicEnemyMaker)),
//     };
// };

#endif // WAVES_HPP_