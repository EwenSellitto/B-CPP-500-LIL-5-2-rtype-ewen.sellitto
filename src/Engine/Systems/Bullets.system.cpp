/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "Engine/Systems/Bullets.system.hpp"

#include "ECS/World.hpp"
#include "Engine/Components/Bullet.component.hpp"
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

void Bullets::tick() {}

void Bullets::spawnBullet(float posx, float posy, float direction, float speed)
{
    using namespace Engine::Components;
    getWorld().createEntity(
        new PositionComponent(posx, posy), new MovingComponent({posx, posy}, 1000 * 10, {direction * (speed * 100), 0}),
        new RenderableComponent("./assets/MainShipWeapons/Mainshipweapon-Projectile-Rocket.png", posx, posy, 2, 0.5),
        new CollisionComponent(0, 0, 100, 100), new BulletComponent(10, speed, direction));
}