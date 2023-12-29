/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Renderer.systems.cpp
*/

#include "Engine/Systems/Renderer.system.hpp"

#include <map>

#include "ECS/Components.hpp"
#include "Engine/Components/Position.compnent.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void Renderer::configure([[maybe_unused]] ECS::World &world) {}

void Renderer::unconfigure() {}

void Renderer::tick()
{
    using namespace Engine::Components;

    ECS::World                &world    = getWorld();
    sf::RenderWindow          *window   = &WINDOW;
    std::vector<ECS::Entity *> entities = world.getEntitiesWithComponents<RenderableComponent, PositionComponent>();
    std::map<int, std::vector<ECS::Entity *>> layer_map = {};

    for (auto entity : entities) {
        auto renderable = entity->getComponent<RenderableComponent>();
        layer_map[renderable->layer].push_back(entity);
    }

    window->clear(sf::Color::Black);
    for (auto layers : layer_map) {
        for (auto entity : layers.second) {
            auto renderable = entity->getComponent<RenderableComponent>();
            auto position   = entity->getComponent<PositionComponent>();

            renderable->sprite.setPosition(position->x, position->y);
            renderable->sprite.setRotation(renderable->rotation);
            renderable->sprite.setScale(renderable->scale);

            window->draw(renderable->sprite);
        }
    }

    window->display();
}
