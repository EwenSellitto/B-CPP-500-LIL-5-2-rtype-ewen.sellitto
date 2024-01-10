/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** RenderEngine.hpp
*/

#pragma once
#include "ECS/World.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/ExcludeCollision.component.hpp"
#include "Engine/Components/Parallax.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Speed.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
#include "R-Type/Components/EnemyMovements.component.hpp"
#include "R-Type/Components/Player.component.hpp"

namespace EnemyMakers
{
    size_t basicEnemyMaker(float y, bool isAttacking);
    size_t mediumEnemyMaker(float y, bool isAttacking);
} // namespace EnemyMakers

extern std::map<size_t, std::function<size_t(float, bool)>> functionMap;
