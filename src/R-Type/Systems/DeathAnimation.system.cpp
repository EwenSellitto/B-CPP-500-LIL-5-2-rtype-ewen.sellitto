/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** DeathAnimation.system.cpp
*/

#include "R-Type/Systems/DeathAnimation.system.hpp"

#include "Engine/Components/Renderable.component.hpp"
#include "R-Type/Components/DeathAnimation.component.hpp"

using namespace Engine::System;

void DeathAnimationSystem::configure(ECS::World &world) {}

void DeathAnimationSystem::unconfigure() {}

void DeathAnimationSystem::tick()
{
    ECS::World                &world = WORLD;
    std::vector<ECS::Entity *> entities =
        world.getEntitiesWithComponents<Engine::Components::RenderableComponent,
                                        Engine::Components::DeathAnimationComponent>();

    for (auto &entity : entities) {
        auto renderable     = entity->getComponent<Engine::Components::RenderableComponent>();
        auto deathAnimation = entity->getComponent<Engine::Components::DeathAnimationComponent>();
        if (renderable->path != deathAnimation->animationPath) {
            renderable->reset(deathAnimation->animationPath, renderable->position, renderable->priority,
                              renderable->rotation, renderable->scale);
        }
        if (deathAnimation->clock.getElapsedTime().asMilliseconds() > deathAnimation->animationSpeed) {
            deathAnimation->clock.restart();
            deathAnimation->frame++;
            if (deathAnimation->frame >= deathAnimation->frameCount) entity->removeAllComponents();
        }
        renderable->sprite.setTextureRect(sf::Rect<int>(
            deathAnimation->textureRect.left + deathAnimation->tileSize.x * deathAnimation->frame,
            deathAnimation->textureRect.top, deathAnimation->textureRect.width, deathAnimation->textureRect.height));
    }
}
