/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Booster.system.cpp
*/

#include "R-Type/Systems/Booster.system.hpp"

#include "ECS/World.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "R-Type/Components/Booster.component.hpp"

using namespace Rtype::System;

static void moveBoosters(std::vector<ECS::Entity *> entities)
{
    for (auto &entity : entities) {
        auto moving  = entity->getComponent<Engine::Components::MovingComponent>();
        auto booster = entity->getComponent<Rtype::Components::BoosterComponent>();
    }
}

void BoosterSystem::tick()
{
    using namespace Rtype::Components;
    using namespace Engine::Components;

    ECS::World world = this->getWorld();

    auto booster_entities        = world.getEntitiesWithComponents<BoosterComponent, MovingComponent>();
    auto weapon_booster_entities = world.getEntitiesWithComponents<WeaponBoosterComponent, MovingComponent>();
}
