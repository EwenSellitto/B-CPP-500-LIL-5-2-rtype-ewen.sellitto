/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** World.hpp
*/

#pragma once

#include "Components.hpp"
#include "Entity.hpp"
#include "Utilities.hpp"
#include <unordered_map>

namespace ECS {
class BaseComponent;
class Entity;

class World
{
    public:
        World();
        ~World();

    private:
        std::unordered_map<id_t, Entity> _entities;
};
} // namespace ECS
