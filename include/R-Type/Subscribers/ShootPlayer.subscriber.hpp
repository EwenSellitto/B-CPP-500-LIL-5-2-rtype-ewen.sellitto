/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** PlayerMove.subscriber.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Player.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "Engine/Systems/Bullets.system.hpp"
#include "Engine/Systems/MovePlayer.system.hpp"

namespace Rtype::Subscriber
{
    class ShootPlayerPressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            ShootPlayerPressedSubscriber()           = default;
            ~ShootPlayerPressedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyPressedEvent &data) override
            {
                using namespace Engine::Components;

                if (data.keyEvent.code != sf::Keyboard::Space) return;
                Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                    Engine::EngineClass::getEngine().world().getSystems()["PlayerMover"].get());
                Engine::System::Bullets *bulletsSystem = dynamic_cast<Engine::System::Bullets *>(
                    Engine::EngineClass::getEngine().world().getSystems()["Bullets"].get());
                ECS::Entity *player =
                    Engine::EngineClass::getEngine().world().getEntityWithComponents<PlayerComponent>();
                if (!player || !movePlayerSystem) return;

                ECS::ComponentHandle<Engine::Components::PositionComponent> pos =
                    player->getComponent<Engine::Components::PositionComponent>();
                bulletsSystem->spawnBullet(static_cast<float>(pos->x), static_cast<float>(pos->y), 1);
            }
    };

    class ShootPlayerReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
    {
        public:
            ShootPlayerReleasedSubscriber()           = default;
            ~ShootPlayerReleasedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyReleasedEvent &data) override
            {
                if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                      data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                    return;
                // Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                //     Engine::EngineClass::getEngine().world().getSystems()["PlayerMover"].get());
                // if (!movePlayerSystem) return;
                // movePlayerSystem->stopMovePlayer(data.keyEvent);
            }
    };
} // namespace Rtype::Subscriber
