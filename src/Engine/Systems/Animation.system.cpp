/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "Engine/Systems/Animation.system.hpp"

#include "ECS/World.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void AnimationSystem::configure([[maybe_unused]] ECS::World &world)
{
    nullptr;
}

void AnimationSystem::unconfigure()
{
    nullptr;
}

void AnimationSystem::tick()
{
    ECS::World                &world    = getWorld();
    std::vector<ECS::Entity *> entities = world.getEntitiesWithComponents<Engine::Components::RenderableComponent,
                                                                          Engine::Components::AnimationComponent>();

    for (auto &entity : entities) {
        auto renderable = entity->getComponent<Engine::Components::RenderableComponent>();
        auto animation  = entity->getComponent<Engine::Components::AnimationComponent>();
        if (animation->clock.getElapsedTime().asMilliseconds() > animation->animationSpeed) {
            animation->clock.restart();
            animation->frame++;
            if (animation->frame >= animation->frameCount) animation->frame = 0;
        }
        renderable->sprite.setTextureRect(
            sf::Rect<int>(
                animation->textureRect.left + animation->tileSize.x * animation->frame,
                animation->textureRect.top,
                animation->textureRect.width,
                animation->textureRect.height
                )
        );
    }
}
