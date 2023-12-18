/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderer.systems.cpp
*/

#include <map>

#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Systems/Renderer.system.hpp"

using namespace Engine::System;

void Renderer::configure([[maybe_unused]] ECS::World &world)
{
    return;
}

void Renderer::unconfigure()
{
    return;
}

void Renderer::tick()
{
    using namespace Engine::Components;

    ECS::World                                                           &world = getWorld();
    std::map<int, std::vector<ECS::ComponentHandle<RenderableComponent>>> components{};

    world.each<RenderableComponent>(
        [&]([[maybe_unused]] ECS::Entity *_, ECS::ComponentHandle<RenderableComponent> renderable) {
            components[renderable->priority].push_back(renderable);
        });
    for (auto &component : components) {
        for (auto &renderable : component.second) {
            renderable->sprite.setPosition(renderable->position.x, renderable->position.y);
            // renderable->sprite.setRotation(renderable->rotation);
            // renderable->sprite.setScale(renderable->scale);
            // renderable->sprite.setColor(renderable->color);
            // getRenderWindow().draw(*renderable->sprite);
        }
    }
}