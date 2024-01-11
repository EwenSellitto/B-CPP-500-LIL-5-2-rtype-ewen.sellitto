// Subscribers.hpp
#pragma once

#include "ECS/World.hpp"
#include "R-Type/Events/EnnemyDeath.event.hpp"
#include "R-Type/Subscribers/Collision.subscriber.hpp"
#include "R-Type/Subscribers/EnnemyDeath.subscriber.hpp"
#include "R-Type/Subscribers/PlayerMove.subscriber.hpp"
#include "R-Type/Subscribers/ShootPlayer.subscriber.hpp"

namespace Subscribers
{
    inline void subscribeToEvents(ECS::World *world)
    {
        auto *subMovePressed  = new Rtype::Subscriber::PlayerMovePressedSubscriber();
        auto *subMoveReleased = new Rtype::Subscriber::PlayerMoveReleasedSubscriber();
        auto *subCollision    = new Rtype::Subscriber::CollisionEventSubscriber();
        auto *subShootPlayer  = new Rtype::Subscriber::ShootPlayerReleasedSubscriber();
        auto *subShootPlayer2 = new Rtype::Subscriber::ShootPlayerPressedSubscriber();
        auto *subEnnemyDeath  = new Rtype::Subscriber::EnnemyDeathSubscriber();

        world->subscribe<KeyPressedEvent>(subMovePressed);
        world->subscribe<KeyReleasedEvent>(subMoveReleased);
        world->subscribe<CollisionEvent>(subCollision);
        world->subscribe<KeyReleasedEvent>(subShootPlayer);
        world->subscribe<KeyPressedEvent>(subShootPlayer2);
        world->subscribe<Rtype::Events::EnnemyDeath>(subEnnemyDeath);
    }
} // namespace Subscribers
