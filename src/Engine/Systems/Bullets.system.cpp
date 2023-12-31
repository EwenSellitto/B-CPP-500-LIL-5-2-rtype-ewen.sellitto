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
#include "Engine/Components/Type.component.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Missile.component.hpp"
#include "Engine/Components/BaseBullet.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void Bullets::configure([[maybe_unused]] ECS::World &world)
{
}

void Bullets::unconfigure()
{
}

void Bullets::tick() {}

void Bullets::spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time)
{
    using namespace Engine::Components;

    getWorld().createEntity(
        new PositionComponent(static_cast<int>(posx), static_cast<int>(posy)),
        new MovingComponent({posx, posy}, time * 10, destination),
        new RenderableComponent("./assets/MainShipWeapons/Mainshipweapon-Projectile-Rocket.png", posx, posy, 2, 90),
        new CollisionComponent(7, 13, 18, 5),
        new AnimationComponent(13, 10, 5, 18, 32, 32, 50, 3),
        new BaseBulletComponent(fromEnemy),
        new MissileComponent());
}

void Bullets::spawnBullet(bool fromEnemy, float posx, float posy, sf::Vector2f destination, size_t time, float rotation)
{
    using namespace Engine::Components;

    getWorld().createEntity(
        new PositionComponent(static_cast<int>(posx), static_cast<int>(posy)),
        new MovingComponent({posx, posy}, time * 10, destination),
        new RenderableComponent("./assets/MainShipWeapons/Mainshipweapon-Projectile-Rocket.png", 0, 0, 2, rotation),
        new CollisionComponent(7, 13, 18, 5),
        new AnimationComponent(13, 10, 5, 18, 32, 32, 50, 3),
        new BaseBulletComponent(fromEnemy),
        new MissileComponent());
}
