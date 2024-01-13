/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** RenderEngine.hpp
*/

#pragma once

#include <SFML/System.hpp>
#include <functional>
#include <map>
#include <vector>

namespace EnemyMakers
{
    std::size_t basicEnemyMaker(float y, bool isAttacking, std::vector<std::pair<std::size_t, sf::Vector2f>>);
    std::size_t mediumEnemyMaker(float y, bool isAttacking, std::vector<std::pair<std::size_t, sf::Vector2f>>);
    std::size_t strongEnemyMaker(float y, bool isAttacking, std::vector<std::pair<std::size_t, sf::Vector2f>>);
    std::size_t ObstacleMaker(float y, bool isAttacking, std::vector<std::pair<std::size_t, sf::Vector2f>>);
} // namespace EnemyMakers

extern std::map<std::size_t, std::function<size_t(float, bool, std::vector<std::pair<size_t, sf::Vector2f>>)>>
    functionMap;
