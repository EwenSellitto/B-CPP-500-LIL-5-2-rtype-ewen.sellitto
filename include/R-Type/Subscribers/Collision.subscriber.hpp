/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Collision.subscriber.hpp
*/

#pragma once

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Events/Collision.event.hpp"

namespace Rtype::Subscriber
{
    class CollisionEventSubscriber : public virtual ECS::EventSubscriber<CollisionEvent>
    {
        public:
            CollisionEventSubscriber()           = default;
            ~CollisionEventSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const CollisionEvent &data) override
            {
                using namespace Engine::Components;

                data.movingEntity->removeComponent<MovingComponent>();
            }
    };
} // namespace Rtype::Subscriber
