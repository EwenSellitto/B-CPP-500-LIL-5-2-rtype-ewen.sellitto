/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** PlayerMove.subscriber.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include "ECS/EventSubscriber.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "R-Type/Systems/MovePlayer.system.hpp"

namespace Rtype::Subscriber
{
    class PlayerMovePressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            PlayerMovePressedSubscriber()           = default;
            ~PlayerMovePressedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyPressedEvent &data) override
            {
                if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                      data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                    return;
                Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                    Engine::EngineClass::getEngine().world().getSystems()["MovePlayer"].get());
                if (!movePlayerSystem) return;
                movePlayerSystem->addMovePlayer(data.keyEvent);
            }
    };

    class PlayerMoveReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
    {
        public:
            PlayerMoveReleasedSubscriber()           = default;
            ~PlayerMoveReleasedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyReleasedEvent &data) override
            {
                if (!(data.keyEvent.code == sf::Keyboard::Z || data.keyEvent.code == sf::Keyboard::Q ||
                      data.keyEvent.code == sf::Keyboard::S || data.keyEvent.code == sf::Keyboard::D))
                    return;
                Engine::System::MovePlayer *movePlayerSystem = dynamic_cast<Engine::System::MovePlayer *>(
                    Engine::EngineClass::getEngine().world().getSystems()["MovePlayer"].get());
                if (!movePlayerSystem) return;
                movePlayerSystem->stopMovePlayer(data.keyEvent);
            }
    };
} // namespace Rtype::Subscriber
