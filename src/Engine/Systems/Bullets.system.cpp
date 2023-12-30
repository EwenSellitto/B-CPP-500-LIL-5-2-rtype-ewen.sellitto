/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "Engine/Systems/Bullets.system.hpp"

#include "ECS/World.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void Bullets::configure([[maybe_unused]] ECS::World &world)
{
    return;
}

void Bullets::unconfigure()
{
    return;
}

void Bullets::tick()
{
    // moveBullet();
}

void Bullets::spawnBullet(float posx, float posy)
{
    using namespace Engine::Components;

    getWorld().createEntity(
        new PositionComponent(posx, posy), new MovingComponent({posx, posy}, 1000 * 100, {speed * 100, 0}),
        new RenderableComponent("./assets/MainShipWeapons/Mainshipweapon-Projectile-Rocket.png", posx, posy, 2, 0.5),
        new CollisionComponent(), new TypeComponent(Engine::Components::TypeComponent::missile));
}

void Bullets::moveBullet()
{
    using namespace Engine::Components;
    for (auto &bullet : bullets) {
        std::cout << "move bullet" << std::endl;
        if (!bullet->has<PositionComponent>()) return;
        ECS::ComponentHandle<PositionComponent> bulletPos(bullet->getComponent<PositionComponent>());
        if (!bullet->has<MovingComponent>()) {
            bullet->addComponent(new MovingComponent(
                {static_cast<float>(bulletPos->x), static_cast<float>(bulletPos->y)}, 1000 * 100, {speed * 100, 0}));
            return;
        }
        bullet->removeComponent<MovingComponent>();
        bullet->addComponent(new MovingComponent({static_cast<float>(bulletPos->x), static_cast<float>(bulletPos->y)},
                                                 1000 * 100, {speed * 100, 0}));
    }
}

void Bullets::addBullet(ECS::Entity *entity)
{
    bullets.push_back(entity);
}