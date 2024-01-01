// Subscribers.hpp
#pragma once
#include "ECS/EventSubscriber.hpp" // Assume this file contains your subscriber classes
#include "ECS/World.hpp"
#include "R-Type/Subscribers/Collision.subscriber.hpp"
#include "R-Type/Subscribers/PlayerMove.subscriber.hpp"
#include "R-Type/Subscribers/ShootPlayer.subscriber.hpp"

namespace Subscribers
{
    void subscribeToEvents(std::shared_ptr<ECS::World> &world)
    {
        auto *subMovePressed  = new Rtype::Subscriber::PlayerMovePressedSubscriber();
        auto *subMoveReleased = new Rtype::Subscriber::PlayerMoveReleasedSubscriber();
        auto *subCollision    = new Rtype::Subscriber::CollisionEventSubscriber();
        auto *subShootPlayer  = new Rtype::Subscriber::ShootPlayerReleasedSubscriber();
        auto *subShootPlayer2 = new Rtype::Subscriber::ShootPlayerPressedSubscriber();

        world->subscribe<KeyPressedEvent>(subMovePressed);
        world->subscribe<KeyReleasedEvent>(subMoveReleased);
        world->subscribe<CollisionEvent>(subCollision);
        world->subscribe<KeyReleasedEvent>(subShootPlayer);
        world->subscribe<KeyPressedEvent>(subShootPlayer2);
    }
} // namespace Subscribers
